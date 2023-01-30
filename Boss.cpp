#include "Header.h"

void Boss::OnCollisionBoundary()
{
	int RandomRotate = rand() % 15 + 1;
	tarRotate += (float)RandomRotate;
}

Boss::Boss()
{
	sprite.LoadAll(TEXT("Assets/Enemy/Boss/stay"));
	spriteRI.scale *= 2.7f;
	GenerateMoveCollisionCircle(150);
	layer = 1;
	moveSpeed = 250.0f;
	tarRotate = rand() % 360 + 1;
}

void Boss::FixedUpdate(float _fixedDeltaTime)
{
	sprite.Update(_fixedDeltaTime);

	float deltaRotate = (tarRotate - curRotate) * _fixedDeltaTime * 10.0f;
	curRotate += deltaRotate;
	moveDirection = MathUtility::DegreeToVector2(curRotate);
	spriteRI.rotate = curRotate;
	Enemy::FixedUpdate(_fixedDeltaTime);
}
