#include "Header.h"

TitleScene::TitleScene()
{
	sprite.LoadAll(TEXT("Assets/Scene/Title"));
	spriteRI.scale = { 1.0f, 1.0f };
	spriteRI.pos = { 960.0f , -540.0f };

	spritetitle.LoadAll(TEXT("Assets/MainMenu/newtitle"));
	spritetitleRI.scale = { 1.0f, 1.0f };
	spritetitleRI.pos = { 600.0f , -300.0f };

	spriteMenu[0].LoadAll(TEXT("Assets/MainMenu/gamestart"));
	spriteMenu[1].LoadAll(TEXT("Assets/MainMenu/gamehow"));
	spriteMenu[2].LoadAll(TEXT("Assets/MainMenu/gamerank"));
	spriteMenu[3].LoadAll(TEXT("Assets/MainMenu/credit"));
	spriteMenu[4].LoadAll(TEXT("Assets/MainMenu/exit"));

	for (int i = 0; i <= 4; i++)
	{
		spriteMenuRI[i].pos = { 600.0f , -600.0f - (i * 100.0f) };
	}

	spriteSelete.LoadAll(TEXT("Assets/MainMenu/selete"));
}

void TitleScene::OnActiveScene()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/menu_click.mp3"), 1);
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/TitleRoom.mp3"), 1);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/menu_click.mp3"), 200);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/TitleRoom.mp3"), 200);
	SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/TitleRoom.mp3"), true);

	NowCurSor = 0;
	spriteSelete.scene = 0;
}

void TitleScene::OnUpdate(float _deltaTime)
{
	if (Input::GetInstance().GetKeyState(VK_ESCAPE) == InputState::DOWN)
		PostQuitMessage(0);

	if (Input::GetInstance().GetKeyState(VK_DOWN) == InputState::DOWN)
		NowCurSor++;

	if (Input::GetInstance().GetKeyState(VK_UP) == InputState::DOWN)
		NowCurSor--;

	if (NowCurSor >= 4)
		NowCurSor = 4;
	if (NowCurSor <= 0)
		NowCurSor = 0;

	if (Input::GetInstance().GetKeyState(VK_SPACE) == InputState::DOWN ||
		Input::GetInstance().GetKeyState(VK_RETURN) == InputState::DOWN)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		spriteSelete.scene = 1;

		switch (NowCurSor)
		{
		case 0:
			SceneManager::GetInstance().RemoveScene(TEXT("GameScene"));
			playerInfo.GetInstance().hp = 5;
			playerInfo.GetInstance().score = 0;
			playerInfo.GetInstance().IsFirstContinue = true;
			playerInfo.GetInstance().IsFirstContinueDestroy = false;
			SceneManager::GetInstance().AddScene(TEXT("GameScene"), new GameScene(0));
			SceneManager::GetInstance().ChangeScene(TEXT("GameScene"));
			break;

		case 1:
			SceneManager::GetInstance().ChangeScene(TEXT("HelpScene"));
			break;

		case 2:
			SceneManager::GetInstance().ChangeScene(TEXT("RankScene"));
			break;

		case 3:
			SceneManager::GetInstance().ChangeScene(TEXT("CreditScene"));
			break;

		case 4:
			SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
			PostQuitMessage(0);
			break;
		}

	}

	for (int i = 0; i <= 4; i++)
	{
		spriteMenu[i].scene = 0;
		if (NowCurSor == i)
		{
			spriteMenu[i].scene = 1;
			spriteSeleteRI.pos = spriteMenuRI[i].pos;
		}
	}
}

void TitleScene::OnFixedUpdate(float _fixedDeltaTime)
{
	sprite.Update(_fixedDeltaTime);
}

void TitleScene::OnRender()
{
	sprite.Render(spriteRI);
	spritetitle.Render(spritetitleRI);

	spriteSelete.Render(spriteSeleteRI);
	for (int i = 0; i <= 4; i++)
		spriteMenu[i].Render(spriteMenuRI[i]);

}

void TitleScene::OnUiRender()
{

}
