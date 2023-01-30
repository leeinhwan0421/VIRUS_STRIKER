#pragma once

class Str : public Object
{
public:

	Sprite sprite;
	SpriteRI spriteRI;
	std::wstring str;

	int type;

	Str(std::wstring _filePath, std::wstring _str , int Type);
	virtual void Update(float _deltaTime) override;
	virtual void LateUpdate(float _deltaTime) override;
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(const CollisionBody& body) override;
};