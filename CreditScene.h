#pragma once
class CreditScene : public Scene
{
public:
	Sprite CreditsBackGround;
	SpriteRI CreditsBackGroundRI;

	Sprite sprite;
	SpriteRI spriteRI;

	CreditScene();
	// Scene을(를) 통해 상속됨
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};

