#pragma once

class EndScene : public Scene
{
public:
	Sprite InitialBackGround;
	SpriteRI InitialBackGroundRI;

	Sprite sprite;
	SpriteRI spriteRI;

	int end;

	Str* str = nullptr;

	int initialCursor = 0;

	int initialNum[3] = { 0,0,0 };

	EndScene(int _end);
	// Scene을(를) 통해 상속됨
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};

