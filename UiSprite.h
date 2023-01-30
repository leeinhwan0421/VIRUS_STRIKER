#pragma once

class UiSprite : public Object
{
public:

	Sprite sprite;
	SpriteRI spriteRI;

	UiSprite(std::wstring _filePath);
	// Object��(��) ���� ��ӵ�
	virtual void Update(float _deltaTime) override;
	virtual void LateUpdate(float _deltaTime) override;
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(const CollisionBody& body) override;
};

