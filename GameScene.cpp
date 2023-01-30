#include "Header.h"

GameScene::GameScene(int _stage)// : stage(_stage)
{
	obm.AddObject(pMap = new Map(stage));
	obm.AddObject(pPlayer = new Player());
	obm.AddObject(pBoss = new Boss());
	obm.AddObject(virus_flash = new Virus_Flash);

	if (_stage == 0)
	{
		virus_speed.resize(3);
		virus_big.resize(2);
		for (int i = 0; i < virus_speed.size(); i++)
		{
			obm.AddObject(virus_speed[i] = new Virus_Speed);
			virus_speed[i]->pos = D3DXVECTOR2(float(pMap->mapWidth / 2 + 1), -float(pMap->mapHeight / 2 + 1));
		}
		for (int i = 0; i < virus_big.size(); i++)
		{
			obm.AddObject(virus_big[i] = new Virus_Big);
			virus_big[i]->pos = D3DXVECTOR2(float(pMap->mapWidth / 2 + 1), -float(pMap->mapHeight / 2 + 1));;
		}
	}

	if (_stage == 1)
	{
		virus_speed.resize(5);
		virus_big.resize(3);
		for (int i = 0; i < virus_speed.size(); i++)
		{
			obm.AddObject(virus_speed[i] = new Virus_Speed);
			virus_speed[i]->pos = D3DXVECTOR2(float(pMap->mapWidth / 2 + 1), -float(pMap->mapHeight / 2 + 1));
		}
		for (int i = 0; i < virus_big.size(); i++)
		{
			obm.AddObject(virus_big[i] = new Virus_Big);
			virus_big[i]->pos = D3DXVECTOR2(float(pMap->mapWidth / 2 + 1), -float(pMap->mapHeight / 2 + 1));;
		}
	}

	stage = _stage;

	pMap->Random(Map::BoundaryPixelState::BOUNDARYEND, pPlayer->pos);
	pBoss->pos = D3DXVECTOR2(float(pMap->mapWidth / 2 + 1), -float(pMap->mapHeight / 2 + 1));
	virus_flash->pos = D3DXVECTOR2(float(pMap->mapWidth / 2 + 1), -float(pMap->mapHeight / 2 + 1));
}

void GameScene::OnActiveScene()
{
	// 사운드 관련 사용 설정
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/menu_click.mp3"), 1);
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/InGame.mp3"), 1);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/menu_click.mp3"), 200);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/InGame.mp3"), 200);
	SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/InGame.mp3"), true);

	if (stage == 0)
	{
		Start = new UiSprite(TEXT("Assets/Ui/Stage_1"));
		Start->pos = D3DXVECTOR2(0.0f, 0.0f);
		obum.AddObject(Start);
	}
	if (stage == 1)
	{
		Start = new UiSprite(TEXT("Assets/Ui/Stage_2"));
		Start->pos = D3DXVECTOR2(0.0f, 0.0f);
		obum.AddObject(Start);
	}

	clear_ = new UiSprite((TEXT("Assets/Ui/Stage_clear")));
	clear_->pos = { 0.0f ,0.0f };
	clear_->spriteRI.a = 0.0f;
	obum.AddObject(clear_);

	Continue = new UiSprite(TEXT("Assets/Ui/Continue"));
	Continue->pos = D3DXVECTOR2(0.0f, 0.0f);

	ContinueNumber = new Number(TEXT("Assets/Ui/Number_3"), ContinueTime);
	ContinueNumber->pos = D3DXVECTOR2(0.0f, -80.0f);

	Start->sprite.scene = 0;

	number = new Number(TEXT("Assets/Ui/Number"), 0);
	number->spriteRI.scale *= 1.2f;
	number->pos = D3DXVECTOR2(-650.0f, 480.0f);
	obum.AddObject(number);

	score = new UiSprite(TEXT("Assets/Ui/Score"));
	score->spriteRI.scale *= 1.2f;
	score->spriteRI.pos = { -800.0f, 480.0f };
	obum.AddObject(score);

	heart = new Heart(0);
	heart->spriteRI.scale *= 1.0f;
	heart->pos = D3DXVECTOR2(-875.0f, 410.0f);
	obum.AddObject(heart);

	time = new Number(TEXT("Assets/Ui/Number_2"), 180);
	time->spriteRI.scale *= 0.8f;
	time->minRenderNumberCount = 3;
	time->pos = D3DXVECTOR2(620.0f, 445.0f);
	obum.AddObject(time);

	auto Timeout = new UiSprite(TEXT("Assets/Ui/Timeout"));
	Timeout->spriteRI.scale *= 0.8f;
	Timeout->spriteRI.pos = { 500.0f, 445.0f };
	obum.AddObject(Timeout);

	point = new Number(TEXT("Assets/Ui/Number_2"), 0);
	point->spriteRI.scale *= 0.8f;
	point->minRenderNumberCount = 2;
	point->pos = D3DXVECTOR2(90.0f, 445.0f);
	obum.AddObject(point);

	auto Nowcure = new UiSprite(TEXT("Assets/Ui/NowCure"));
	Nowcure->spriteRI.scale *= 0.7f;
	Nowcure->spriteRI.pos = { -50.0f, 445.0f };
	obum.AddObject(Nowcure);
}

void GameScene::OnUpdate(float _deltaTime)
{	
	if (IsFirstRevive == true && (pMap->szFillPixel / (float)pMap->szPixel) > 0.5f)
	{
		if (stage == 0)
		{
			virus_speed.resize(2);
			virus_big.resize(1);
			for (int i = 0; i < virus_speed.size(); i++)
			{
				obm.AddObject(virus_speed[i] = new Virus_Speed);
				virus_speed[i]->pos = pBoss->pos;
			}
			for (int i = 0; i < virus_big.size(); i++)
			{
				obm.AddObject(virus_big[i] = new Virus_Big);
				virus_big[i]->pos = pBoss->pos;
			}
		}

		if (stage == 1)
		{
			virus_speed.resize(3);
			virus_big.resize(2);
			for (int i = 0; i < virus_speed.size(); i++)
			{
				obm.AddObject(virus_speed[i] = new Virus_Speed);
				virus_speed[i]->pos = pBoss->pos;
			}
			for (int i = 0; i < virus_big.size(); i++)
			{
				obm.AddObject(virus_big[i] = new Virus_Big);
				virus_big[i]->pos = pBoss->pos;
			}
		}

		IsFirstRevive = false;
	}
}

void GameScene::OnFixedUpdate(float _fixedDeltaTime)
{
	Start->sprite.Update(_fixedDeltaTime);

	if (Start->sprite.scene >= Start->sprite.szScene - 1)
	{
		Start->destroy = true;
	}

	if (Input::GetInstance().GetKeyState(VK_F4) == InputState::DOWN)
	{
		SceneManager::GetInstance().ChangeScene(TEXT("TitleScene"));
	}

	if (Input::GetInstance().GetKeyState(VK_F5) == InputState::DOWN)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		if (stage == 1)
		{
			SceneManager::GetInstance().AddScene(TEXT("GameScene"), new GameScene(0));
			SceneManager::GetInstance().ChangeScene(TEXT("GameScene"));
		}
	}

	if ((pMap->szFillPixel / (float)pMap->szPixel) > 0.8f)
	{
		number->pos = { -50.0f , -280.0f };
		score->spriteRI.pos = { -200.0f, -280.0f };
		if (stage == 0)
		{
			clear_->spriteRI.a = 1.0f;
			if (clear_->sprite.scene <= clear_->sprite.szScene - 2)
			{
				clear_->sprite.Update(_fixedDeltaTime);
			}
			if (clear_->sprite.scene >= clear_->sprite.szScene - 2)
			{
				SceneManager::GetInstance().AddScene(TEXT("GameScene_1"), new GameScene(1));
				SceneManager::GetInstance().ChangeScene(TEXT("GameScene_1"));
			}
		}
		if (stage == 1)
		{
			clear_->spriteRI.a = 1.0f;
			if (clear_->sprite.scene <= clear_->sprite.szScene - 2)
			{
				clear_->sprite.Update(_fixedDeltaTime);
			}
			if (clear_->sprite.scene >= clear_->sprite.szScene - 2)
			{ 
				SceneManager::GetInstance().ChangeScene(TEXT("EndScene"));
			}
		}
	}

	if (Input::GetInstance().GetKeyState(VK_F6) == InputState::DOWN)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		if (stage == 0)
		{ 
			SceneManager::GetInstance().RemoveScene(TEXT("GameScene_1"));
			SceneManager::GetInstance().AddScene(TEXT("GameScene_1"), new GameScene(1));
			SceneManager::GetInstance().ChangeScene(TEXT("GameScene_1"));
		}
		if (stage == 1)
		{
			SceneManager::GetInstance().RemoveScene(TEXT("EndScene"));
			SceneManager::GetInstance().AddScene(TEXT("EndScene"), new EndScene(0));
			SceneManager::GetInstance().ChangeScene(TEXT("EndScene"));
		}
	}

	if (Input::GetInstance().GetKeyState(VK_F7) == InputState::DOWN || ClearTime <= 0.3f)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		SceneManager::GetInstance().RemoveScene(TEXT("EndScene_1"));
		SceneManager::GetInstance().AddScene(TEXT("EndScene_1"), new EndScene(1));
		SceneManager::GetInstance().ChangeScene(TEXT("EndScene_1"));
	}

	number->number = playerInfo.GetInstance().score;
	time->number = (int)ClearTime;
	point->number = (int((pMap->szFillPixel / (float)pMap->szPixel) * 100));
	heart->hp = playerInfo.GetInstance().hp;

	ClearTime -= _fixedDeltaTime;
	FlashVirusTIme -= _fixedDeltaTime;

	if (FlashVirusTIme <= 0.0f)	{
		auto virus = new Virus_Flash();
		if (!pMap->Random(Map::PixelState::CLOSE, virus, virus->pos))
		{
			assert(0);
		}
		obm.AddObject(virus);
		FlashVirusTIme = 3.0f;
	}

	if (ContinueTime <= 0.3f)
	{
		SceneManager::GetInstance().RemoveScene(TEXT("EndScene_1"));
		SceneManager::GetInstance().AddScene(TEXT("EndScene_1"), new EndScene(1));
		SceneManager::GetInstance().ChangeScene(TEXT("EndScene_1"));
	}

	if (playerInfo.GetInstance().IsFirstContinue == true && playerInfo.GetInstance().hp == 0)
	{
		if (playerInfo.GetInstance().IsFirstContinueDestroy == false)
		{
			obum.AddObject(Continue);
			obum.AddObject(ContinueNumber);
			playerInfo.GetInstance().IsFirstContinue = false;
			ContinueNumber->minRenderNumberCount = 1;
			ContinueTime = 5.9f;
		}

		if (playerInfo.GetInstance().IsFirstContinueDestroy == true)
		{
			if (pPlayer->sprite.scene <= pPlayer->sprite.szScene - 2)
			{
				SceneManager::GetInstance().AddScene(TEXT("EndScene_1"), new EndScene(1));
				SceneManager::GetInstance().ChangeScene(TEXT("EndScene_1"));
			}
		}
	}

	ContinueNumber->number = ContinueTime;

	if (playerInfo.GetInstance().IsFirstContinue == false)
	{
		if (Input::GetInstance().GetKeyState(VK_SPACE) == InputState::DOWN)
		{
			SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
			playerInfo.GetInstance().hp = 5;
			obm.AddObject(pPlayer = new Player());
			if (!pMap->Random(Map::BoundaryPixelState::BOUNDARY, pPlayer->pos))
				pMap->Random(Map::BoundaryPixelState::BOUNDARYEND, pPlayer->pos);
			playerInfo.GetInstance().IsFirstContinue = true;
			playerInfo.GetInstance().IsFirstContinueDestroy = true;
			Continue->destroy = true;
			ContinueNumber->destroy = true;
		}
		ContinueTime -= _fixedDeltaTime;
	}
}

void GameScene::OnRender()
{
}

void GameScene::OnUiRender()
{
}
