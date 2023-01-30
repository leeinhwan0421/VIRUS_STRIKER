#include "Header.h"

IntroScene::IntroScene()
{
	sprite.LoadAll(TEXT("Assets/Intro"));
	spriteRI.pos = { 960.0f , -540.0f };
	spriteRI.scale = {1.0f, 1.0f};
}

void IntroScene::OnActiveScene()
{
;
}

void IntroScene::OnUpdate(float _deltaTime)
{
}

void IntroScene::OnFixedUpdate(float _fixedDeltaTime)
{
	sprite.Update(_fixedDeltaTime);

	if (sprite.scene >= sprite.szScene - 7)
	{
		SceneManager::GetInstance().ChangeScene(TEXT("TitleScene"));
	}
	if (Input::GetInstance().IfKeyPressed)
	{
		SceneManager::GetInstance().ChangeScene(TEXT("TitleScene"));
	}
}

void IntroScene::OnRender()
{
	sprite.Render(spriteRI);
}

void IntroScene::OnUiRender()
{
}
