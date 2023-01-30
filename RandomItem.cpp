#include "Header.h"

void RandomItem::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

RandomItem::RandomItem()
{
	sprite.LoadAll(TEXT("Assets/item/randomitem"));

	moveSpeed = 100.0f;
	//tarRotate = rand() % 360 + 1;
	layer = 1;
}

void RandomItem::FixedUpdate(float _fixedDeltaTime)
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
		scene->pPlayer->curItem = rand() % 4 + 1;
		switch (scene->pPlayer->curItem)
		{
		case 1:

			scene->pPlayer->ItemSpritePlayTime = 180.0f;
			scene->pPlayer->IsDefense = true;
			scene->pPlayer->i_frame = 1.0f;

			break;
		case 2:

			scene->pPlayer->ItemSpritePlayTime = 1.0f;

			if (playerInfo.GetInstance().hp >= 5)
			{
				playerInfo.GetInstance().score += 15000;
			}
			else
			{
				playerInfo.GetInstance().hp++;
			}

			break;
		case 3:

			scene->pPlayer->curItem = 3;
			scene->pPlayer->moveSpeed = 370.0f;
			scene->pPlayer->ItemSpritePlayTime = 180.0f;

			break;
		case 4:

			scene->pPlayer->i_frame = 4.0f;
			scene->pPlayer->ItemSpritePlayTime = 4.0f;
			break;
		}
		OnDead();
		destroy = true;
		return;
	}
}