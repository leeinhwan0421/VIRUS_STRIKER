#include "Header.h"

Map::Map(int _stage)
{
	spriteCureChangeMap.LoadAll(TEXT("Assets/effect/curechange/manywhite"));
	spriteCureChangeMap.aniLoop = false;
	spriteInfectionMap.LoadAll(TEXT("Assets/Map/Stage") + std::to_wstring(_stage) + TEXT("/Infection"));
	spriteInfectionMap.CreateMaskTexture(colors[static_cast<int>(PixelState::CLOSE)]);
	spriteCureMap.LoadAll(TEXT("Assets/Map/Stage") + std::to_wstring(_stage) + TEXT("/Cure"));
	spriteBoundaryMap.LoadAll(TEXT("Assets/Map/Stage") + std::to_wstring(_stage) + TEXT("/Boundary"));
	spriteBoundaryMap.CreateMaskTexture(boundaryColors[static_cast<int>(BoundaryPixelState::NONE)]);
	mapWidth = spriteInfectionMap.maskWidth;
	mapHeight = spriteInfectionMap.maskHeight;
	for (int i = 0; i < mapWidth; ++i)
	{
		spriteBoundaryMap.maskBit[i] = boundaryColors[int(BoundaryPixelState::BOUNDARYEND)];
		spriteBoundaryMap.maskBit[(mapHeight - 1) * mapWidth + i] = boundaryColors[int(BoundaryPixelState::BOUNDARYEND)];
	}
	for (int i = 0; i < mapHeight; ++i)
	{
		spriteBoundaryMap.maskBit[mapWidth * i] = boundaryColors[int(BoundaryPixelState::BOUNDARYEND)];
		spriteBoundaryMap.maskBit[mapWidth * i + (mapWidth - 1)] = boundaryColors[int(BoundaryPixelState::BOUNDARYEND)];
	}
	//spriteBoundaryMap.UpdateMaskTexture();
	spriteRI.center = D3DXVECTOR2(0.0f, 1.0f);
	szPixel = mapWidth * mapHeight;
	assert(mapWidth % 2 == 1);
	assert(mapHeight % 2 == 1);
	assert(mapWidth == spriteBoundaryMap.maskWidth);
	assert(mapHeight == spriteBoundaryMap.maskHeight);
}

void Map::Update(float _deltaTime)
{
	if (isFloodFill == true)
	{
		spriteCureChangeMap.scene = 0;
		isFloodFill = false;
	}
}

void Map::LateUpdate(float _deltaTime)
{
}

void Map::FixedUpdate(float _fixedDeltaTime)
{
	spriteCureChangeMap.Update(_fixedDeltaTime);
	spriteInfectionMap.Update(_fixedDeltaTime);
	spriteCureMap.Update(_fixedDeltaTime);
}

void Map::Render()
{
	spriteInfectionMap.UpdateMaskTexture();
	spriteBoundaryMap.UpdateMaskTexture();

	spriteRI.pos = pos;
	spriteCureMap.Render(spriteRI);
	spriteCureChangeMap.Render(spriteRI);
	spriteInfectionMap.Render(spriteRI);
	spriteBoundaryMap.Render(spriteRI);
}

void Map::OnCollision(const CollisionBody& body)
{
}

BOOL Map::IsOutBound(D3DXVECTOR2 _pos)
{
	int x = int(_pos.x);
	int y = int(_pos.y);
	if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight)
		return true;
	return false;
}

D3DCOLOR Map::GetPixel(D3DXVECTOR2 _pos)
{
	int x = int(_pos.x);
	int y = int(_pos.y);
	return spriteInfectionMap.maskBit[y * mapWidth + x];
}

Map::PixelState Map::GetPixelState(D3DXVECTOR2 _pos)
{
	for (int i = 0; i<int(PixelState::COUNT); ++i)
	{
		if (GetPixel(_pos) == colors[i])
			return PixelState(i);
	}
	assert(0);
	return PixelState::COUNT;
}

D3DCOLOR Map::GetBoundaryPixel(D3DXVECTOR2 _pos)
{
	int x = int(_pos.x);
	int y = int(_pos.y);
	return spriteBoundaryMap.maskBit[y * mapWidth + x];
}

Map::BoundaryPixelState Map::GetBoundaryPixelState(D3DXVECTOR2 _pos)
{
	for (int i = 0; i<int(BoundaryPixelState::COUNT); ++i)
	{
		if (GetBoundaryPixel(_pos) == boundaryColors[i])
			return BoundaryPixelState(i);
	}
	assert(0);
	return BoundaryPixelState::COUNT;
}

void Map::UpdateMovePath(D3DXVECTOR2 _pos)
{
	int x = int(_pos.x);
	int y = int(_pos.y);
	if (movePath.size() > 0 && x == movePath.back().x && y == movePath.back().y)
	{
		assert(0);
	}
	movePath.push_back({ x, y });
	if (GetBoundaryPixel(_pos) == boundaryColors[int(BoundaryPixelState::NONE)])
		spriteBoundaryMap.UpdateMaskTexture(x, y, boundaryColors[int(BoundaryPixelState::MOVEPATH)]);
}

void Map::RemoveLastMovePath()
{
	if (GetBoundaryPixelState(D3DXVECTOR2(float(movePath.back().x), float(movePath.back().y))) == BoundaryPixelState::MOVEPATH)
		spriteBoundaryMap.UpdateMaskTexture(movePath.back().x, movePath.back().y, boundaryColors[int(BoundaryPixelState::NONE)]);

	movePath.erase(movePath.end() - 1);
}

void Map::ClearMovePath()
{
	for (auto& movePos : movePath)
	{
		if (GetBoundaryPixel(D3DXVECTOR2(float(movePos.x), float(movePos.y))) == boundaryColors[int(BoundaryPixelState::MOVEPATH)])
			spriteBoundaryMap.UpdateMaskTexture(movePos.x, movePos.y, boundaryColors[int(BoundaryPixelState::NONE)]);
	}
	movePath.clear();
}

void Map::CalcFloodFill()
{
	for (auto& movePos : movePath)
	{
		++szFillPixel;
		spriteInfectionMap.maskBit[movePos.y * mapWidth + movePos.x] = colors[int(PixelState::OPEN)];
	}

	std::vector<std::thread> threads(2);
	int threadCount = 0;
	auto ep = movePath[movePath.size() - 2];
	for (int i = 0; i < _countof(DirectionWay4); ++i)
	{
		float x = float(ep.x + DirectionWay4[i].x);
		float y = float(ep.y + DirectionWay4[i].y);
		if (GetBoundaryPixelState(D3DXVECTOR2(x, y)) == BoundaryPixelState::NONE)
		{
			threads[threadCount] = std::thread(&Map::FloodFill, this, D3DXVECTOR2(x, y));
			++threadCount;
		}
	}

	// 2개 (FloodFill 스레드), 1개 (Main Thread) = 3개
	for (auto& thread : threads)
	{
		thread.join();
	}

	movePath.clear();
	//spriteInfectionMap.UpdateMaskTexture();
	//spriteBoundaryMap.UpdateMaskTexture();
}

bool Map::Random(PixelState _state, D3DXVECTOR2& _out)
{
	int random = (randomDevice() % (mapWidth * mapHeight / 2)) * 2;
	for (int i = 0; i < mapWidth * mapHeight; i += 2)
	{
		int idx = (random + i) % (mapWidth * mapHeight - 1);
		if (spriteInfectionMap.maskBit[idx] == colors[int(_state)])
		{
			_out.x = float(idx % mapWidth);
			_out.y = -float(idx / mapWidth);
			return true;
		}
	}
	return false;
}

bool Map::Random(BoundaryPixelState _state, D3DXVECTOR2& _out)
{
	int random = (randomDevice() % (mapWidth * mapHeight / 2)) * 2;
	for (int i = 0; i < mapWidth * mapHeight; i += 2)
	{
		int idx = (random + i) % (mapWidth * mapHeight - 1);
		if (spriteBoundaryMap.maskBit[idx] == boundaryColors[int(_state)])
		{
			_out.x = float(idx % mapWidth);
			_out.y = -float(idx / mapWidth);
			return true;
		}
	}
	return false;
}

bool Map::Random(PixelState _state, const Entity* _entity, D3DXVECTOR2& _out)
{
	int szMap = mapWidth * mapHeight;
	int random = randomDevice() % szMap;

	for (int i = 0; i < szMap; ++i)
	{
		int IDX = (random + i) % szMap;
		float x = float(IDX % mapWidth);
		//float y = float(IDX / mapWidth);
		float y = float(IDX / mapWidth);
		bool condition = true;
		// moveCollisionOffset 을 모두 돌면서 생성이 가능한 위치를 찾습니다.
		for (auto& offset : _entity->moveCollisionOffsets)
		{
			D3DXVECTOR2 p = D3DXVECTOR2(x + offset.x, y + offset.y);
			// BoundaryEnd 때문에 1만큼의 오프셋을 두어 IsOutBound 처리를 합니다.
			if (int(p.x) <= 1 || int(p.y) <= 1 || int(p.x) >= mapWidth - 1 || int(p.y) >= mapHeight - 1)
			{
				condition = false;
				break;
			}
			// 컬러가 다르다면 실패.
			if (GetPixelState(p) != _state)
			{
				condition = false;
				break;
			}
		}
		if (condition)
		{
			_out.x = x;
			_out.y = -y;
			return true;
		}
	}
	return false;
}

void Map::FloodFill(D3DXVECTOR2 _pos)
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());

	int fillCount = 0;
	std::vector<D3DCOLOR> _colors(mapWidth * mapHeight);
	memcpy(&_colors[0], &spriteInfectionMap.maskBit[0], mapWidth * mapHeight * sizeof(D3DCOLOR));
	std::vector<D3DCOLOR> _boundaryColors(mapWidth * mapHeight);
	memcpy(&_boundaryColors[0], &spriteBoundaryMap.maskBit[0], mapWidth * mapHeight * sizeof(D3DCOLOR));

	std::queue<POINT> nodes;
	nodes.push(POINT{ int(_pos.x), int(_pos.y) });
	while (!nodes.empty())
	{
		auto node = nodes.front();
		nodes.pop();

		if (int(scene->pBoss->pos.x) == node.x && -int(scene->pBoss->pos.y) == node.y)
			return;

		auto fPosition = D3DXVECTOR2(float(node.x), float(node.y));
		if (IsOutBound(fPosition))
			continue;

		if (_colors[node.y * mapWidth + node.x] == colors[int(PixelState::OPEN)])
		{
			if (_boundaryColors[node.y * mapWidth + node.x] == boundaryColors[int(BoundaryPixelState::BOUNDARY)] ||
				_boundaryColors[node.y * mapWidth + node.x] == boundaryColors[int(BoundaryPixelState::BOUNDARYEND)])
			{
				_boundaryColors[node.y * mapWidth + node.x] = boundaryColors[int(BoundaryPixelState::NONE)];
			}
			continue;
		}

		++fillCount;
		_colors[node.y * mapWidth + node.x] = colors[int(PixelState::OPEN)];
		for (int i = 0; i < _countof(DirectionWay8); ++i)
			nodes.push({ DirectionWay8[i].x + node.x, DirectionWay8[i].y + node.y });
	}

	for (auto& movePos : movePath)
	{
		_boundaryColors[movePos.y * mapWidth + movePos.x] = boundaryColors[int(BoundaryPixelState::BOUNDARY)];
	}

	spriteInfectionMap.maskBit = _colors;
	spriteBoundaryMap.maskBit = _boundaryColors;
	szFillPixel += fillCount;
	if ((fillCount / 20) > 1)
	{
		srand(time(NULL));
		RandomSpawnOfItem(rand() % 20 + 1);
	}
	playerInfo.GetInstance().score += fillCount / 20;
	isFloodFill = true;
}

void Map::RandomSpawnOfItem(int A)
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	Item* NewItem = nullptr;
	switch (A)
	{
	case 1:
		NewItem = new DefenseItem();
		if (!Random(Map::PixelState::CLOSE, NewItem, NewItem->pos))
		{
			assert(0);
		}
		scene->obm.AddObject(NewItem);
		break;

	case 2:
		NewItem = new HealItem();
		if (!Random(Map::PixelState::CLOSE, NewItem, NewItem->pos))
		{
			assert(0);
		}
		scene->obm.AddObject(NewItem);
		break;

	case 3:
		NewItem = new invincible();
		if (!Random(Map::PixelState::CLOSE, NewItem, NewItem->pos))
		{
			assert(0);
		}
		scene->obm.AddObject(NewItem);
		break;

	case 4:
		NewItem = new SpeedItem();
		if (!Random(Map::PixelState::CLOSE, NewItem, NewItem->pos))
		{
			assert(0);
		}
		scene->obm.AddObject(NewItem);
		break;

	case 5:
		NewItem = new RandomItem();
		if (!Random(Map::PixelState::CLOSE, NewItem, NewItem->pos))
		{
			assert(0);
		}
		scene->obm.AddObject(NewItem);
		break;
	}
}