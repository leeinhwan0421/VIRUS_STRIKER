#pragma once

class IntroScene : public Scene
{
public:
	Sprite sprite;
	SpriteRI spriteRI;

	IntroScene();
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};

