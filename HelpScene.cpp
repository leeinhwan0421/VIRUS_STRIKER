#include "Header.h"

HelpScene::HelpScene()
{
	HTPkBackground.LoadAll(TEXT("Assets/Scene/Title"));
	HTPkBackgroundRI.scale = D3DXVECTOR2(1.5f, 1.5f);
	HTPkBackgroundRI.pos = D3DXVECTOR2(960.0f, -540.0f);

	CurSor.LoadAll(TEXT("Assets/MainMenu/selete"));
	CurSorRI.scale = D3DXVECTOR2(1.5f, 1.5f);
	CurSor.aniTime = 1.0f;

	HTPMain.LoadAll(TEXT("Assets/Scene/defulat"));
	HTPMainRI.scale = D3DXVECTOR2(1.0f, 1.0f);
	HTPMainRI.pos = D3DXVECTOR2(960.0f, -540.0f);

	for (int i = 0; i < 3; ++i)
	{
		Menu[i].LoadAll(TEXT("Assets/Scene/HelpScene/HelpList") + std::to_wstring(i));
		MenuRI[i].scale = D3DXVECTOR2(1.3f, 1.3f);
	}

	MenuRI[0].pos = D3DXVECTOR2(960.0f, -340.0f);
	MenuRI[1].pos = D3DXVECTOR2(960.0f, -540.0f);
	MenuRI[2].pos = D3DXVECTOR2(960.0f, -740.0f);
}

void HelpScene::OnActiveScene()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/menu_click.mp3"), 1);
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/HTPRoom.mp3"), 1);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/menu_click.mp3"), 200);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/HTPRoom.mp3"), 200);
	SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/HTPRoom.mp3"),true);
	
	for (int i = 0; i < 3; ++i)
		Menu[i].scene = 0;

	NowCurSor = 0;
	CurSor.scene = 0;
}

void HelpScene::OnUpdate(float _deltaTime)
{

	if (Input::GetInstance().GetKeyState(VK_ESCAPE) == InputState::DOWN)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		SceneManager::GetInstance().ChangeScene(TEXT("TitleScene"));
	}

	if (NowCurSor > 0 & (Input::GetInstance().GetKeyState(VK_UP) == InputState::DOWN))
	{
		NowCurSor--;
	}

	if (NowCurSor < 2 & (Input::GetInstance().GetKeyState(VK_DOWN) == InputState::DOWN))
	{
		NowCurSor++;
	}

	if (Input::GetInstance().GetKeyState(VK_RETURN) == InputState::DOWN || Input::GetInstance().GetKeyState(VK_SPACE) == InputState::DOWN)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		SceneManager::GetInstance().ChangeScene(TEXT("HTPs") + std::to_wstring(NowCurSor));
		CurSor.scene = 1;
	}

	for (int i = 0; i < 3; ++i)
	{
		Menu[i].scene = 0;
		if (NowCurSor == i)
		{
			Menu[i].scene = 1;
			CurSorRI.pos = MenuRI[i].pos;
		}
	}
}

void HelpScene::OnFixedUpdate(float _fixedDeltaTime)
{

}

void HelpScene::OnRender()
{
	HTPkBackground.Render(HTPkBackgroundRI);
	HTPMain.Render(HTPMainRI);

	CurSor.Render(CurSorRI);
	for (int i = 0; i < 3; ++i)
		Menu[i].Render(MenuRI[i]);
}

void HelpScene::OnUiRender()
{

}

HTPs::HTPs(int _htpnumber)
{
	this->htpnumber = _htpnumber;

	HTP.LoadAll(TEXT("Assets/Scene/HelpScene/Help") + std::to_wstring(htpnumber));
	HTPRI.scale = D3DXVECTOR2(1.0f, 1.0f);
	HTPRI.pos = D3DXVECTOR2(960.0f, -540.0f);

	HTPkBackground.LoadAll(TEXT("Assets/Scene/Title"));
	HTPkBackgroundRI.scale = D3DXVECTOR2(1.5f, 1.5f);
	HTPkBackgroundRI.pos = D3DXVECTOR2(960.0f, -540.0f);
}

void HTPs::OnActiveScene()
{
	//SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/menu_click.mp3"), 1);
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/MusicSurround.mp3"), 1);
	SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/MusicSurround.mp3"), true);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/MusicSurround.mp3"), 500);
}

void HTPs::OnUpdate(float _deltaTime)
{
	if (Input::GetInstance().GetKeyState(VK_LEFT) == InputState::DOWN)
	{
		if ((htpnumber - 1) <= -1)
			SceneManager::GetInstance().ChangeScene(TEXT("HelpScene"));
		else
			SceneManager::GetInstance().ChangeScene(TEXT("HTPs") + std::to_wstring((htpnumber - 1)));
	}

	else if (Input::GetInstance().GetKeyState(VK_RIGHT) == InputState::DOWN)
	{
		if ((htpnumber + 1) >= 3)
			SceneManager::GetInstance().ChangeScene(TEXT("HelpScene"));
		else
			SceneManager::GetInstance().ChangeScene(TEXT("HTPs") + std::to_wstring((htpnumber + 1)));
	}

	else if (Input::GetInstance().IfKeyPressed)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		SceneManager::GetInstance().ChangeScene(TEXT("HelpScene"));
	}

	HTP.Update(_deltaTime);
}

void HTPs::OnRender()
{
	HTPkBackground.Render(HTPkBackgroundRI);
	HTP.Render(HTPRI);
}