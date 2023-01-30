#include "Header.h"

void Enemy::OnFrameMove(const FrameMoveResult& _result)
{
	// 플레이어의 죽음 이벤트를 확인합니다.
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());

	if (_result.IsplayerDead == true)
	{
		scene->pPlayer->OnDead();
	}

	// 픽셀에 Enemy의 정보를 갱신합니다.
	for (auto& offset : moveCollisionOffsets)
	{
		scene->pMap->spriteBoundaryMap.UpdateMaskTexture(int(pos.x + offset.x), -int(pos.y + offset.y), scene->pMap->boundaryColors[int(Map::BoundaryPixelState::NONE)]);
	}
	for (auto& offset : moveCollisionOffsets)
	{
		scene->pMap->spriteBoundaryMap.UpdateMaskTexture(int(_result.np.x + offset.x), -int(_result.np.y + offset.y), scene->pMap->boundaryColors[int(Map::BoundaryPixelState::ENEMY)]);
	}
}

bool Enemy::IsFrameMove(const FrameMoveCondition& _condition, FrameMoveResult& _result)
{
	// 경계선에 충돌 한 경우에는 따로 이벤트를 저장 할 필요가 없습니다.
	// 이동에 실패하면 더 이상 이동 시도를 하지 않습니다. (return 값이 false 인 경우)
	// 따라서 다음과 같이 간략하게 처리합니다.

	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());

	if (_condition.npbps == Map::BoundaryPixelState::BOUNDARY || _condition.npbps == Map::BoundaryPixelState::BOUNDARYEND)
	{
		OnCollisionBoundary();
		return false;
	}

	// 만약 scene에 배치된 플레이어의 아이템코드가 1(방어막) , 4(무적) 일 경우 충돌처리를 진행합니다.

	if (scene->pPlayer->i_frame >= 0.0f)
	{
		if (_condition.npbps == Map::BoundaryPixelState::MOVEPATH)
		{
			OnCollisionBoundary();
			return false;
		}
	}

	// 충돌 범위에 플레이어의 이동 경로가 포함 된 경우
	// 플레이어의 죽음을 처리하기 위해 이벤트를 저장합니다.
	if (_condition.npbps == Map::BoundaryPixelState::MOVEPATH)
	{
		_result.IsplayerDead = true;
	}

	return true;
}

void Enemy::OnDead()
{
	// 픽셀에 Enemy의 정보를 갱신합니다.
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	for (auto& offset : moveCollisionOffsets)
	{
		scene->pMap->spriteBoundaryMap.UpdateMaskTexture(int(pos.x + offset.x), -int(pos.y + offset.y), scene->pMap->boundaryColors[int(Map::BoundaryPixelState::NONE)]);
	}
	destroy = true;
}

void Enemy::FixedUpdate(float _fixedDeltaTime)
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	if (scene->pMap->GetPixelState({ pos.x, -pos.y }) == Map::PixelState::OPEN)
	{
		OnDead();
		return;
	}
	Entity::FixedUpdate(_fixedDeltaTime);
}
