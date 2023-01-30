#include "Header.h"

Number::Number(std::wstring _filePath, int _number)
{
	sprite.LoadAll(_filePath);
	number = _number;
}

void Number::Update(float _deltaTime)
{
}

void Number::LateUpdate(float _deltaTime)
{
}

void Number::FixedUpdate(float _fixedDeltaTime)
{
}

void Number::Render()
{
	// 미리 해당 Number의 갯수를 가져옵니다.
	int _numberCount = 0;
	int _number = number;
	while (_number != 0)
	{
		++_numberCount;
		_number /= 10;
	}

	// 숫자의 갯수만큼 그리거나 최소한으로 그려줘야 하는 갯수만큼 그립니다.
	_numberCount = max(_numberCount, minRenderNumberCount);

	// 숫자를 그려줍니다.
	_number = number;
	for (int i = _numberCount - 1; i >= 0; --i)
	{
		spriteRI.pos = pos + D3DXVECTOR2(70.0f * i, 0.0f);
		sprite.scene = _number % 10;
		sprite.Render(spriteRI);
		_number = _number / 10;
	}
}

void Number::OnCollision(const CollisionBody& body)
{
}
