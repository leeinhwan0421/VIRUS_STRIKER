#include "Header.h"

void Virus_Flash::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

Virus_Flash::Virus_Flash()
{
	tag = TEXT("Virus_Flash");
	sprite.LoadAll(TEXT("Assets/Enemy/Virus_Flash/unflash"));
	spriteRI.scale *= 2.0f;
	moveSpeed = 200.0f;
	collisionLayer = 1;
	layer = 1;
	tarRotate = rand() % 360 + 1;
	GenerateMoveCollisionCircle(30);
}

void Virus_Flash::FixedUpdate(float _fixedDeltaTime)
{

	if (firstSpawn == true && sprite.scene >= sprite.szScene - 7)
	{
		sprite.LoadAll(TEXT("Assets/Enemy/Virus_Flash/stay"));
		sprite.scene = 0;
		firstSpawn = false;
	}
	if (FlashTime <= 0.0f)
	{
		if (changeSprite == false)
		{
			sprite.LoadAll(TEXT("Assets/Enemy/Virus_Flash/flash"));
			changeSprite = true;
		}
		if (sprite.scene >= sprite.szScene - 1)
		{
			OnDead();
			return;
		}
	}

	sprite.Update(_fixedDeltaTime);

	FlashTime -= _fixedDeltaTime;

	float deltaRotate = (tarRotate - curRotate) * _fixedDeltaTime * 10.0f;
	curRotate += deltaRotate;
	moveDirection = MathUtility::DegreeToVector2(curRotate);
	spriteRI.rotate = curRotate;
	Enemy::FixedUpdate(_fixedDeltaTime);
}