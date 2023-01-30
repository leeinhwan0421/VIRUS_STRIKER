#include "Header.h"

void Player::OnFrameIntervalDirectionUpdate()
{
	// �÷��̾�� �ڷ� ������ ���� �ֽ��ϴ�.
	// �� �� �̵� ��θ� ����� �̵��ؾ� �ϸ�, �̵� ��θ� ���� �������� �ϱ� ������ ������ ���� ó���մϴ�.
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());

	if (scene->pMap->movePath.size() > 2)
	{
		// integer current position
		POINT icp = scene->pMap->movePath[scene->pMap->movePath.size() - 1];
		// integer prev position
		POINT ipp = scene->pMap->movePath[scene->pMap->movePath.size() - 2];
		POINT dp = POINT{ ipp.x - icp.x, -(ipp.y - icp.y) };
		moveDirection = D3DXVECTOR2(float(dp.x), float(dp.y));
		scene->pMap->RemoveLastMovePath();
		scene->pMap->RemoveLastMovePath();
		if (scene->pMap->movePath.size() == 1)
			scene->pMap->RemoveLastMovePath();
	}
}

bool Player::IsFrameMove(const FrameMoveCondition& _condition, FrameMoveResult& _result)
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());

	// �÷��̾ ��輱�� �ִ� ���
	if (_condition.cpbps == Map::BoundaryPixelState::BOUNDARY || _condition.cpbps == Map::BoundaryPixelState::BOUNDARYEND)
	{
		// ���� ��ġ�� ��輱 �� ��쿡�� �̵��� �����ϴ�.
		if (_condition.npbps == Map::BoundaryPixelState::BOUNDARY || _condition.npbps == Map::BoundaryPixelState::BOUNDARYEND)
			return true;

		// �����̽��ٸ� ������ �ִٸ� Ž���� �����Ѵ�.
		else if (Input::GetInstance().GetKeyState(VK_SPACE) && _condition.npps == Map::PixelState::CLOSE)
		{
			scene->pMap->UpdateMovePath({ pos.x, -pos.y });
			scene->pMap->UpdateMovePath({ _condition.np.x, -_condition.np.y });
			return true;
		}
	}

	// �÷��̾ ��輱 �ٱ��� �ִ� ���
	else if (!frameIntervalDirectionUpdate)
	{
		scene->pMap->UpdateMovePath({ _condition.np.x, -_condition.np.y });

		// ��輱�� ���� �� ��� ���� ĥ�մϴ�.
		if (_condition.npbps == Map::BoundaryPixelState::BOUNDARYEND || _condition.npbps == Map::BoundaryPixelState::BOUNDARY)
		{
			scene->pMap->CalcFloodFill();
			return true;
		}
		// ��ֹ��� �����Ͽ��ٸ� �̵��� ����մϴ�.
		else if (_condition.npbps == Map::BoundaryPixelState::OBSTACLE)
		{
			return false;
		}
		// �÷��̾��� �̵� ��ο� ������ ��ġ�Ѵٸ� �÷��̾ ����մϴ�.
		else if (_condition.npbps == Map::BoundaryPixelState::ENEMY)
		{
			OnDead();
			return false;
		}
		// �̵� ��ο� �ε����ٸ� ����մϴ�.
		else if (_condition.npbps == Map::BoundaryPixelState::MOVEPATH)
		{
			i_frame = 0.0f;
			scene->pPlayer->OnDead();
			return false;
		}

		return true;
	}
	else
	{
		return true;
	}

	return false;
}

void Player::OnDead()
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	auto GetPlayersPos = scene->pMap->GetBoundaryPixelState(scene->pPlayer->pos); //�̰� �� �÷��̾ ������� �����ϴ� ��������

	if (IsDefense == false)
	{
		if (i_frame <= 0.0f)
		{
			// �÷��̾ ����ϸ� �̵���ο� ��ġ�� �ʱ�ȭ�մϴ�.
			moveDirection = { 0.0f, 0.0f };
			playerInfo.GetInstance().hp--;

			scene->pMap->ClearMovePath();
			if (!scene->pMap->Random(Map::BoundaryPixelState::BOUNDARY, pos))
				scene->pMap->Random(Map::BoundaryPixelState::BOUNDARYEND, pos);
			frameIntervalDirectionUpdate = false;

			curItem = 0;
		}
	}

	else
	{
		moveDirection = { 0.0f, 0.0f };
		IsDefense = false;

		scene->pMap->ClearMovePath();

		if (!scene->pMap->Random(Map::BoundaryPixelState::BOUNDARY, pos))
			scene->pMap->Random(Map::BoundaryPixelState::BOUNDARYEND, pos);

		frameIntervalDirectionUpdate = false;
		curItem = 0;
	}
}

Player::Player()
{
	collisionLayer = 1;
	layer = 1;
	fMinFrameInterval = 2.0f;
	MinFrameInterval = 2;

	sprite.LoadAll(TEXT("Assets/Player/status5"));

	ItemSprite[0].LoadAll(TEXT("Assets/itemEffect/shieldeffect"));
	ItemSprite[1].LoadAll(TEXT("Assets/itemEffect/healeffect"));
	ItemSprite[2].LoadAll(TEXT("Assets/itemEffect/speedeffect"));
	ItemSprite[3].LoadAll(TEXT("Assets/itemEffect/mujeokeffect"));
}

void Player::ItemAbility(float _ItemAnimationTime)
{
	if (curItem == 3)
	{
		moveSpeed = 370.0f;
	}
	else
	{
		moveSpeed = 300.0f;
	}

	i_frame -= _ItemAnimationTime;
	ItemSpritePlayTime -= _ItemAnimationTime;

	for (int i = 0; i < 4; i++)
	{
		ItemSprite[i].Update(_ItemAnimationTime);
	}
}

void Player::Cheating()
{
	if (Input::GetInstance().GetKeyState(VK_F1) == InputState::DOWN)
	{
		i_frame = 5.0f;
	}
	if (Input::GetInstance().GetKeyState(VK_F3) == InputState::DOWN)
	{
		if(playerInfo.GetInstance().hp < 5)
		playerInfo.GetInstance().hp++;
	}

	if (Input::GetInstance().GetKeyState(VK_F8))
	{
		playerInfo.GetInstance().score += 11;
	}
}

void Player::FixedUpdate(float _fixedDeltaTime)
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	auto cpbps = scene->pMap->GetBoundaryPixelState({ pos.x, -pos.y });
	bool isMove = frameIntervalDirectionUpdate = false;

	sprite.Update(_fixedDeltaTime);

	if (curItem == 3)
	{
		moveSpeed = 370.0f;
	}
	else
	{
		moveSpeed = 300.0f;
	}

	if (curItem == 1)
	{
		IsDefense = true;
	}
	else
	{
		IsDefense = false;
	}

	if (cpbps == Map::BoundaryPixelState::BOUNDARY || cpbps == Map::BoundaryPixelState::BOUNDARYEND)
	{
		isMove = true;
	}

	else
	{
		isMove = true;
		if (Input::GetInstance().GetKeyState(VK_SPACE) == InputState::NONE)
			frameIntervalDirectionUpdate = true;
	}

	moveDirection = { 0.0f, 0.0f };

	if (isMove)
	{
		if (Input::GetInstance().GetKeyState(VK_LEFT))
			moveDirection.x -= 1.0f;
		if (Input::GetInstance().GetKeyState(VK_RIGHT))
			moveDirection.x += 1.0f;
		if (Input::GetInstance().GetKeyState(VK_UP))
			moveDirection.y += 1.0f;
		if (Input::GetInstance().GetKeyState(VK_DOWN))
			moveDirection.y -= 1.0f;
	}

	ItemAbility(_fixedDeltaTime);
	Cheating();

	if (playerInfo.GetInstance().hp > 0)
		sprite.LoadAll(TEXT("Assets/Player/status") + std::to_wstring(playerInfo.GetInstance().hp));
	else
	{
		sprite.LoadAll(TEXT("Assets/Player/die"));
		sprite.aniLoop = false;
		sprite.aniTime = 1.0f;
		moveSpeed = 0.0f;
		if (sprite.scene <= sprite.szScene - 1)
			destroy = true;
	}

	Entity::FixedUpdate(_fixedDeltaTime);

	Direct3D::GetInstance().cameraPos = { pos.x , pos.y };

	assert(int(pos.x) % 2 == 0);
	assert(int(pos.y) % 2 == 0);
}

void Player::Render()
{
	Entity::Render();

	for (int i = 0; i < 4; i++)
	{
		ItemSpriteRI[i].rotate = spriteRI.rotate;

		if (curItem - 1 == i && ItemSpritePlayTime >= 0.0f)
		{
			ItemSpriteRI[i].rotate = spriteRI.rotate;

			ItemSpriteRI[i].pos = spriteRI.pos;
			if (curItem == 3)
			{
				ItemSpriteRI[i].pos.y = spriteRI.pos.y - 70.0f;
			}
			ItemSpriteRI[i].a = 1.0f;
			ItemSprite[i].Render(ItemSpriteRI[i]);
		}
		else
		{
			ItemSpriteRI[i].a = 0.0f;
		}
	}
}