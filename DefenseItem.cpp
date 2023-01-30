#include "Header.h"

void DefenseItem::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

DefenseItem::DefenseItem()
{
	sprite.LoadAll(TEXT("Assets/item/shielditem"));

	moveSpeed = 100.0f;
	//tarRotate = rand() % 360 + 1;
	layer = 1;
}

void DefenseItem::FixedUpdate(float _fixedDeltaTime)
{
	sprite.Update(_fixedDeltaTime);
	auto scene = static_cast<GameScene*>(SceneManager::GetInstance().GetActiveScene());
	auto cpps = scene->pMap->GetPixelState({ pos.x, -pos.y });

	float deltaRotate = (tarRotate - curRotate) * _fixedDeltaTime * 10.0f;
	curRotate += deltaRotate;
	moveDirection = MathUtility::DegreeToVector2(curRotate);
	spriteRI.rotate = curRotate;
	//Item::FixedUpdate(_fixedDeltaTime);

	if (cpps == Map::PixelState::OPEN)
	{
		scene->pPlayer->curItem = 1;
		scene->pPlayer->ItemSpritePlayTime = 180.0f;
		scene->pPlayer->IsDefense = true;
		scene->pPlayer->i_frame = 1.0f;
		OnDead();
		destroy = true;
		return;
	}
}