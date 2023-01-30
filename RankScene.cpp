#include "Header.h"

RankScene::RankScene(RankInfo _rankInfo)
{
	RankBackGround.LoadAll(TEXT("Assets/Scene/Title"));
	RankBackGroundRI.scale = D3DXVECTOR2(1.5f, 1.5f);
	RankBackGroundRI.pos = D3DXVECTOR2(960.0f, -540.0f);

	sprite.LoadAll(TEXT("Assets/Scene/RankScene"));
	spriteRI.pos = { 960.0f , -540.0f };

	// vector ��ũ�� ũ�⸦ �����մϴ�.
	ranks.resize(MaxRank);

	// ���Ϸκ��� ��ũ ������ �н��ϴ�.
	std::wifstream is(TEXT("Assets/rank.txt"));

	// ������ ���ȴ� �� Ȯ���մϴ�.
	if (is.is_open())
	{
		// ��ũ ������ �н��ϴ�.
		for (int i = 0; i < MaxRank; ++i)
		{
			is >> ranks[i].score;
			is >> ranks[i].initial;
		}
	}

	// ����
	ranks.push_back(_rankInfo);
	std::sort(ranks.begin(), ranks.end(), [](const RankInfo& _lhs, const RankInfo& _rhs) {
		return _lhs.score > _rhs.score;
	});
	ranks.erase(ranks.end() - 1);

	// ���Ϸκ��� ��ũ ������ ���ϴ�..
	std::wofstream os(TEXT("Assets/rank.txt"));
	for (int i = 0; i < MaxRank; ++i)
	{
		os << ranks[i].score << std::endl;
		os << ranks[i].initial << std::endl;
	}
}

void RankScene::OnActiveScene()
{
	// ���� ���� ��� ����
	// sound ���ú��� �����ϴ� ����� ã�ƺ���,,
	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/menu_click.mp3"), 1);
	SoundManager::GetInstance().Create(TEXT("Assets/SoundFX/RankRoom.mp3"), 1);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/menu_click.mp3"), 200);
	SoundManager::GetInstance().SetVolume(TEXT("Assets/SoundFX/RankRoom.mp3"), 200);
	SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/RankRoom.mp3"), true);

	D3DXVECTOR2 startPosition = D3DXVECTOR2(-200.f, 200.0f);
	for (int i = 0; i<int(ranks.size()); ++i)
	{
		auto str = new Str(TEXT("Assets/Ui/Initial"), ranks[i].initial , 0);
		str->spriteRI.scale *= 0.8f;
		auto number = new Number(TEXT("Assets/Ui/Number"), ranks[i].score);
		number->spriteRI.scale *= 1.5f;
		str->pos = startPosition + D3DXVECTOR2(-250.0f , -240.0f * i);
		number->pos = startPosition + D3DXVECTOR2(150.0f, -240.0f * i);

		obum.AddObject(str);
		obum.AddObject(number);
	}
}

void RankScene::OnUpdate(float _deltaTime)
{
	if (Input::GetInstance().IfKeyPressed)
	{
		SoundManager::GetInstance().Play(TEXT("Assets/SoundFX/menu_click.mp3"));
		SceneManager::GetInstance().ChangeScene(TEXT("TitleScene"));
	}
}

void RankScene::OnFixedUpdate(float _fixedDeltaTime)
{
}

void RankScene::OnRender()
{
	RankBackGround.Render(RankBackGroundRI);
	sprite.Render(spriteRI);
}

void RankScene::OnUiRender()
{
}
