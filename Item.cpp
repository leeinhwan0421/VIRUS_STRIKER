#include "Header.h"

bool Item::IsFrameMove(const FrameMoveCondition& _condition, FrameMoveResult& _result)
{
	// ��輱�� �浹 �� ��쿡�� ���� �̺�Ʈ�� ���� �� �ʿ䰡 �����ϴ�.
	// �̵��� �����ϸ� �� �̻� �̵� �õ��� ���� �ʽ��ϴ�. (return ���� false �� ���)
	// ���� ������ ���� �����ϰ� ó���մϴ�.
	if (_condition.npbps == Map::BoundaryPixelState::BOUNDARY || _condition.npbps == Map::BoundaryPixelState::BOUNDARYEND)
	{
		OnCollisionBoundary();
		return false;
	}

	// �浹 ������ �÷��̾��� �̵� ��ΰ� ���� �� ���
	// �÷��̾��� ������ ó���ϱ� ���� �̺�Ʈ�� �����մϴ�.
	if (_condition.npbps == Map::BoundaryPixelState::MOVEPATH)
	{
		_result.bps.push_back(_condition.npbps);
	}

	return true;
}

void Item::OnDead()
{
	// �ȼ��� Enemy�� ������ �����մϴ�.
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	for (auto& offset : moveCollisionOffsets)
	{
		scene->pMap->spriteBoundaryMap.UpdateMaskTexture(int(pos.x + offset.x), -int(pos.y + offset.y), scene->pMap->boundaryColors[int(Map::BoundaryPixelState::NONE)]);
	}
	destroy = true;
}

void Item::FixedUpdate(float _fixedDeltaTime)
{
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	if (scene->pMap->GetPixelState({ pos.x, -pos.y }) == Map::PixelState::OPEN)
	{
		OnDead();
		return;
	}
	Entity::FixedUpdate(_fixedDeltaTime);
}
