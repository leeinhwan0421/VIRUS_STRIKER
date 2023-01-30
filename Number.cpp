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
	// �̸� �ش� Number�� ������ �����ɴϴ�.
	int _numberCount = 0;
	int _number = number;
	while (_number != 0)
	{
		++_numberCount;
		_number /= 10;
	}

	// ������ ������ŭ �׸��ų� �ּ������� �׷���� �ϴ� ������ŭ �׸��ϴ�.
	_numberCount = max(_numberCount, minRenderNumberCount);

	// ���ڸ� �׷��ݴϴ�.
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
