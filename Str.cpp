#include "Header.h"

Str::Str(std::wstring _filePath, std::wstring _str, int Type)
{
	type = Type;
	sprite.LoadAll(_filePath);
	str = _str;
	for (int i = 0; i < int(str.length()); ++i)
		str[i] = towupper(str[i]);
}

void Str::Update(float _deltaTime)
{
}

void Str::LateUpdate(float _deltaTime)
{
}

void Str::FixedUpdate(float _fixedDeltaTime)
{
}

void Str::Render()
{
	if (type == 0)
	{
		for (int i = 0; i<int(str.length()); ++i)
		{
			assert(str[i] >= 'A' || str[i] <= '[');
			spriteRI.pos = pos + D3DXVECTOR2(i * 100.0f, 0.0f);
			sprite.scene = str[i] - 'A';
			sprite.Render(spriteRI);
		}
	}
	if (type == 1)
	{
		for (int i = 0; i<int(str.length()); ++i)
		{
			assert(str[i] >= 'A' || str[i] <= '[');
			spriteRI.pos = pos + D3DXVECTOR2(i * 210.0f, 0.0f);
			sprite.scene = str[i] - 'A';
			sprite.Render(spriteRI);
		}
	}
}

void Str::OnCollision(const CollisionBody& body)
{
}
