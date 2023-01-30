#include "Header.h"

void HealItem::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

HealItem::HealItem()
{
	sprite.LoadAll(TEXT("Assets/item/healitem"));

	moveSpeed = 100.0f;
	//tarRotate = rand() % 360 + 1;
	layer = 1;
}

void HealItem::FixedUpdate(float _fixedDeltaTime)
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
		scene->pPlayer->curItem = 2;
		scene->pPlayer->ItemSpritePlayTime = 1.0f;

		if (playerInfo.GetInstance().hp >= 5)
		{
			playerInfo.GetInstance().score += 15000;
		}
		else
		{
			playerInfo.GetInstance().hp++;
		}

		OnDead();
		destroy = true;
		return;
	}
}