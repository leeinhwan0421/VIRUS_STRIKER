#include "Header.h"

CreditScene::CreditScene()
{
	CreditsBackGround.LoadAll(TEXT("Assets/Scene/Title"));
	CreditsBackGroundRI.scale = D3DXVECTOR2(1.5f, 1.5f);
	CreditsBackGroundRI.pos = D3DXVECTOR2(960.0f, -540.0f);

	sprite.LoadAll(TEXT("Assets/Scene/Credit"));
	spriteRI.scale = { 1.0f, 1.0f };
	spriteRI.pos = { 960.0f , -540.0f };
}

void CreditScene::OnActiveScene()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/menu_click.mp3"), 1);
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/CreditsRoom.mp3"), 1);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/menu_click.mp3"), 200);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/CreditsRoom.mp3"), 200);
	SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/CreditsRoom.mp3"), false);
}

void CreditScene::OnUpdate(float _deltaTime)
{
	if (Input::GetInstance().IfKeyPressed)
	{
		SceneManager::GetInstance().ChangeScene(TEXT("TitleScene"));
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
	}
}

void CreditScene::OnFixedUpdate(float _fixedDeltaTime)
{
	sprite.Update(_fixedDeltaTime);
}

void CreditScene::OnRender()
{
	CreditsBackGround.Render(CreditsBackGroundRI);
	sprite.Render(spriteRI);
}

void CreditScene::OnUiRender()
{

}
