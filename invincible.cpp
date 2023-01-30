#include "Header.h"

void invincible::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

invincible::invincible()
{
	sprite.LoadAll(TEXT("Assets/item/mujeokitem"));

	moveSpeed = 100.0f;
	//tarRotate = rand() % 360 + 1;
	layer = 1;
}

void invincible::FixedUpdate(float _fixedDeltaTime)
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
		scene->pPlayer->curItem = 4;
		// 4.0f 초 동안 무적
		scene->pPlayer->i_frame = 4.0f;
		scene->pPlayer->ItemSpritePlayTime = 4.0f;
		OnDead();
		destroy = true;
		return;
	}
}