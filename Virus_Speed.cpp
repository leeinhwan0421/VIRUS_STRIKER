#include "Header.h"

void Virus_Speed::OnCollisionBoundary()
{
	int RandomRotate = rand() % 7 + 1;
	tarRotate += (float)RandomRotate;

	moveSpeed = 600.0f;
}

Virus_Speed::Virus_Speed()
{
	tag = TEXT("Virus_Speed");
	sprite.LoadAll(TEXT("Assets/Enemy/Virus_Speed/stay"));
	spriteRI.scale *= 1.0f;
	moveSpeed = 280.0f;	
	collisionLayer = 1;
	layer = 1;
	tarRotate = rand() % 360 + 1;
	GenerateMoveCollisionCircle(20);
}

void Virus_Speed::FixedUpdate(float _fixedDeltaTime)
{
	moveSpeed -= _fixedDeltaTime * 100.0f;
	if (moveSpeed <= 280.0f)
	{
		moveSpeed = 280.0f;
	}
	sprite.Update(_fixedDeltaTime);
	float deltaRotate = (tarRotate - curRotate) * _fixedDeltaTime * 10.0f;
	curRotate += deltaRotate;
	moveDirection = MathUtility::DegreeToVector2(curRotate);
	spriteRI.rotate = curRotate;
	Enemy::FixedUpdate(_fixedDeltaTime);
}
