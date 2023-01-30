#pragma once

class GameScene : public Scene
{
public:

	int stage = 0;
	Map* pMap = nullptr;
	Player* pPlayer = nullptr;

	Boss* pBoss = nullptr;
	Virus_Flash* virus_flash = nullptr;

	std::vector<Virus_Speed*> virus_speed;
	std::vector<Virus_Big*> virus_big;

	// 스코어와 점령포인트와 하트 
	Number* number = nullptr;
	Number* point = nullptr;
	Heart* heart = nullptr;

	UiSprite* score = nullptr;

	// 게임 시작시 나오는 애니메이션
	UiSprite* Start = nullptr;

	// 게임 클리어시 나오는 애니메이션
	UiSprite* clear_ = nullptr;

	// 죽을 시 컨디뉴 애니메이션
	UiSprite* Continue = nullptr;
	Number* ContinueNumber = nullptr;
	//bool IsFirstContinue = true;
	//bool IsFirstContinueDestroy = false;
	float ContinueTime = 5.0f;

	// Flash_Virus의 재생성 타임.
	float FlashVirusTIme = 5.0f;

    // 제한시간에 관한 
	Number* time = nullptr;
	float ClearTime = 180.0f;

	// 바이러스 재생성이 한번만
	bool IsFirstRevive = true;

	GameScene(int _stage);
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};
