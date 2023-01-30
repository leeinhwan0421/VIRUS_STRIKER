#pragma once
class Heart : public Object
{
public:
	Sprite sprite;
	SpriteRI spriteRI;

	int hp;
	int hpState[5] = { 0,0,0,0,0 };

	Heart(int _hp);
	// Object을(를) 통해 상속됨
	virtual void Update(float _deltaTime) override;
	virtual void LateUpdate(float _deltaTime) override;
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(const CollisionBody& body) override;
};

