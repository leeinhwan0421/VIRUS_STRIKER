#include "Header.h"

void Virus_Big::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

Virus_Big::Virus_Big()
{
	sprite.LoadAll(TEXT("Assets/Enemy/Virus_Big/stay"));
	spriteRI.scale *= 2.0f;
	moveSpeed = 100.0f;
	layer = 1;

	tarRotate = rand() % 360 + 1;

	GenerateMoveCollisionCircle(120);
}

void Virus_Big::FixedUpdate(float _fixedDeltaTime)
{
	sprite.Update(_fixedDeltaTime);
	float deltaRotate = (tarRotate - curRotate) * _fixedDeltaTime * 10.0f;
	curRotate += deltaRotate;
	moveDirection = MathUtility::DegreeToVector2(curRotate);
	spriteRI.rotate = curRotate;
	Enemy::FixedUpdate(_fixedDeltaTime);
}

