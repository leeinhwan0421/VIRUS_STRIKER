#include "Header.h"

void SpeedItem::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

SpeedItem::SpeedItem()
{
	sprite.LoadAll(TEXT("Assets/item/speeditem"));

	moveSpeed = 100.0f;
	//tarRotate = rand() % 360 + 1;
	layer = 1;
}

void SpeedItem::FixedUpdate(float _fixedDeltaTime)
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
		scene->pPlayer->curItem = 3;
		scene->pPlayer->moveSpeed = 370.0f;
		scene->pPlayer->ItemSpritePlayTime = 180.0f;
		OnDead();
		destroy = true;
		return;
	}
}