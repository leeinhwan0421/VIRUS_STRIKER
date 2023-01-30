#pragma once

class Number : public Object
{
public:

	Sprite sprite;
	SpriteRI spriteRI;
	int number = 0;
	int minRenderNumberCount = 6;

	Number(std::wstring _filePath, int _number);
	virtual void Update(float _deltaTime) override;
	virtual void LateUpdate(float _deltaTime) override;
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(const CollisionBody& body) override;
};