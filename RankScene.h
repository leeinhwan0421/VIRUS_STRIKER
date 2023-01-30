#pragma once

class RankScene : public Scene
{
public:

	Sprite RankBackGround;
	SpriteRI RankBackGroundRI;

	Sprite sprite;
	SpriteRI spriteRI;

	struct RankInfo
	{
		int score = 0;
		std::wstring initial = TEXT("AAA");
	};
	static const int MaxRank = 3;
	std::vector<RankInfo> ranks;

	RankScene(RankInfo _rankInfo);
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};