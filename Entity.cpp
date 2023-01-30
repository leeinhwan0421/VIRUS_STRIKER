#include "Header.h"

void Entity::GenerateMoveCollisionCircle(int _radius)
{
	moveCollisionOffsets.clear();
	for (int i = 1 - _radius; i < _radius; ++i)
	{
		for (int j = 1 - _radius; j < _radius; ++j)
		{
			float len1 = float(pow(i, 2) + pow(j, 2));
			if (len1 < pow(_radius, 2) && len1 > pow(_radius - 2.0f, 2))
				moveCollisionOffsets.push_back(D3DXVECTOR2(float(i), float(j)));
		}
	}
}

void Entity::GenerateMoveCollisionBox(int _minx, int _miny, int _maxx, int _maxy)
{
	for (int i = 1 + _minx; i < _maxx; ++i)
	{
		moveCollisionOffsets.push_back(D3DXVECTOR2(float(i), float(_miny)));
		moveCollisionOffsets.push_back(D3DXVECTOR2(float(i), float(_maxy)));
	}
	for (int j = 1 + _miny; j < _maxy; ++j)
	{
		moveCollisionOffsets.push_back(D3DXVECTOR2(float(_minx), float(j)));
		moveCollisionOffsets.push_back(D3DXVECTOR2(float(_maxx), float(j)));
	 } 
} 

void Entity::FrameMove(const D3DXVECTOR2& _direction)
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	for (int i = 0; i < MinFrameInterval; ++i)
	{
		FrameMoveResult ret;
		ret.np = pos + _direction;

		for (auto& offset : moveCollisionOffsets)
		{
			auto np = ret.np + offset;
			if (scene->pMap->IsOutBound({ np.x, -np.y }))
				return;

			FrameMoveCondition condition;
			condition.cpbps = scene->pMap->GetBoundaryPixelState({ pos.x, -pos.y });
			condition.cpps = scene->pMap->GetPixelState({ pos.x, -pos.y });
			condition.npbps = scene->pMap->GetBoundaryPixelState({ np.x, -np.y });
			condition.npps = scene->pMap->GetPixelState({ np.x, -np.y });
			condition.np = np;

			if (IsFrameMove(condition, ret) == false)
			{
				return;
			}
		}

		OnFrameMove(ret);
		pos = ret.np;
	}
}

void Entity::FixedUpdate(float _fixedDeltaTime)
{
	if (!frameIntervalDirectionUpdate && D3DXVec2Length(&moveDirection) == 0.0f)
		return;

	moveLength += moveSpeed * _fixedDeltaTime;
	while (moveLength >= fMinFrameInterval)
	{
		if (frameIntervalDirectionUpdate)
		{
			OnFrameIntervalDirectionUpdate();
			if (D3DXVec2Length(&moveDirection) == 0.0f)
			{
				moveLength = 0.0f;
				break;
			}
		}

		D3DXVECTOR2 direction = moveDirection;

		if (direction.x != 0.0f && direction.y != 0.0f)
		{
			if (stairEvent) direction.x = 0.0f;
			else direction.y = 0.0f;
			stairEvent = !stairEvent;
		}
		FrameMove(direction);
		moveLength -= fMinFrameInterval;
	}
}

void Entity::Render()
{
	spriteRI.pos = pos;
	sprite.Render(spriteRI);
}

void Entity::OnCollision(const CollisionBody& body)
{
}
