#include "Header.h"

void Enemy::OnFrameMove(const FrameMoveResult& _result)
{
	// �÷��̾��� ���� �̺�Ʈ�� Ȯ���մϴ�.
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());

	if (_result.IsplayerDead == true)
	{
		scene->pPlayer->OnDead();
	}

	// �ȼ��� Enemy�� ������ �����մϴ�.
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
	// ��輱�� �浹 �� ��쿡�� ���� �̺�Ʈ�� ���� �� �ʿ䰡 �����ϴ�.
	// �̵��� �����ϸ� �� �̻� �̵� �õ��� ���� �ʽ��ϴ�. (return ���� false �� ���)
	// ���� ������ ���� �����ϰ� ó���մϴ�.

	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());

	if (_condition.npbps == Map::BoundaryPixelState::BOUNDARY || _condition.npbps == Map::BoundaryPixelState::BOUNDARYEND)
	{
		OnCollisionBoundary();
		return false;
	}

	// ���� scene�� ��ġ�� �÷��̾��� �������ڵ尡 1(��) , 4(����) �� ��� �浹ó���� �����մϴ�.

	if (scene->pPlayer->i_frame >= 0.0f)
	{
		if (_condition.npbps == Map::BoundaryPixelState::MOVEPATH)
		{
			OnCollisionBoundary();
			return false;
		}
	}

	// �浹 ������ �÷��̾��� �̵� ��ΰ� ���� �� ���
	// �÷��̾��� ������ ó���ϱ� ���� �̺�Ʈ�� �����մϴ�.
	if (_condition.npbps == Map::BoundaryPixelState::MOVEPATH)
	{
		_result.IsplayerDead = true;
	}

	return true;
}

void Enemy::OnDead()
{
	// �ȼ��� Enemy�� ������ �����մϴ�.
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
