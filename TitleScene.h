#pragma once

class TitleScene : public Scene
{
public:
	Sprite sprite;
	SpriteRI spriteRI;

	Sprite spritetitle;
	SpriteRI spritetitleRI;

	Sprite spriteMenu[5];
	SpriteRI spriteMenuRI[5];

	Sprite spriteSelete;
	SpriteRI spriteSeleteRI;

	int NowCurSor;

	TitleScene();
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};

