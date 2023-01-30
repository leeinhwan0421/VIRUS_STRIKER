#include "Header.h"

Heart::Heart(int _hp)
{
	sprite.LoadAll(TEXT("Assets/Ui/Heart"));
	hp = _hp;
}

void Heart::Update(float _deltaTime)
{
	
}

void Heart::LateUpdate(float _deltaTime)
{
}

void Heart::FixedUpdate(float _fixedDeltaTime)
{
	if (hp >= 5)
	{
		hp = 5;
	}
	for (int i = 0; i < 5; i++)
	{
		hpState[i] = 0;
	}

	for (int i = 0; i < hp; i++)
	{
		hpState[i] = 1;
	}
}

void Heart::Render()
{
	for (int i = 0; i < 5; ++i)
	{
		spriteRI.pos = pos + D3DXVECTOR2(1.0f + (i * 70.0f), 0.0f);
		sprite.scene = hpState[i];
		sprite.Render(spriteRI);
	}
}

void Heart::OnCollision(const CollisionBody& body)
{
}
