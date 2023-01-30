#include "Header.h"

EndScene::EndScene(int _end)
{
	end = _end;

	if (_end == 0)
	{
		InitialBackGround.LoadAll(TEXT("Assets/Scene/Title"));
		InitialBackGroundRI.scale = D3DXVECTOR2(1.5f, 1.5f);
		InitialBackGroundRI.pos = D3DXVECTOR2(960.0f, -540.0f);

		sprite.LoadAll(TEXT("Assets/Scene/EndScene"));
		sprite.scene = 0;
		spriteRI.scale = { 1.0f, 1.0f };
		spriteRI.pos = { 960.0f , -540.0f };
		initialCursor = 0;

		for (int i = 0; i < 3; i++)
		{
			initialNum[i] = 0;
		}
		for (int i = 0; i < 3; i++)
		{
			str = new Str(TEXT("Assets/Ui/Initial"), TEXT("[[[") , 1);
			str->spriteRI.scale *= 0.8f;
			str->pos = D3DXVECTOR2(-200.0f, -120.0f);

			obum.AddObject(str);

		}
	}
	if (_end == 1)
	{
		sprite.LoadAll(TEXT("Assets/Scene/EndScene"));
		sprite.scene = 1;
		spriteRI.scale = { 1.0f, 1.0f };
		spriteRI.pos = { 960.0f , -540.0f };
	}
}

void EndScene::OnActiveScene()
{
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/menu_click.mp3"), 1);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/menu_click.mp3"), 200);

	if (end == 0)
	{
		SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/AllClear.mp3"), 1);
		SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/AllClear.mp3"), 200);
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/AllClear.mp3"), false);
		auto score = new Number(TEXT("Assets/Ui/Number_2"), playerInfo.GetInstance().score);
		score->spriteRI.scale *= 1.0f;
		score->minRenderNumberCount = 6;
		score->pos = D3DXVECTOR2(-450.0f, 355.0f);
		obum.AddObject(score);
	}

	else
	{
		SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/GameOver.mp3"), 1);
		SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/GameOver.mp3"), 200);
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/GameOver.mp3"), false);
	}
}

void EndScene::OnUpdate(float _deltaTime)
{
	if (end == 0)
	{
		for (int i = 'A'; i < 'Z' + 1; i++)
		{
			if (Input::GetInstance().GetKeyState(i) == InputState::DOWN)
			{
				if (initialCursor < 3)
				{
					initialNum[initialCursor] = i;
					initialCursor++;
				}
			}
		}

		if (Input::GetInstance().GetKeyState(VK_BACK) == InputState::DOWN)
		{
			if (initialCursor >= 0)
			{
				initialNum[initialCursor] = 91;
				initialCursor--;
			}
		}

		if (initialCursor >= 3)
		{
			initialCursor = 2;
		}

		if (initialCursor < 0)
		{
			initialCursor = 0;
		}
	}

	if (end == 0)
	{
		std::wstring initial;

		for (int i = 0; i < 3; ++i)
			initial.push_back(initialNum[i]);

		if (Input::GetInstance().GetKeyState(VK_RETURN) == InputState::DOWN && initialCursor == 2)
		{
			SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
			SceneManager::GetInstance().RemoveScene(TEXT("RankScene"));
			SceneManager::GetInstance().AddScene(TEXT("RankScene"), new RankScene({ playerInfo.GetInstance().score, initial }));
			SceneManager::GetInstance().ChangeScene(TEXT("CreditScene"));
		}
	}

	if (end == 1)
	{
		if (Input::GetInstance().IfKeyPressed)
		{
			SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
			SceneManager::GetInstance().ChangeScene(TEXT("CreditScene"));
		}
	}
}

void EndScene::OnFixedUpdate(float _fixedDeltaTime)
{
}

void EndScene::OnRender()
{
	InitialBackGround.Render(InitialBackGroundRI);
	sprite.Render(spriteRI);

	if (end == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			if (initialNum[i] != 0)
			{
				if (initialNum[i] - 'A' >= 0)
				{
					str->str[i] = initialNum[i];
				}
			}
		}
	}
}

void EndScene::OnUiRender()
{
}
