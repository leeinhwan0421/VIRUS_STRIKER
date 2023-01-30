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

	// ���ھ�� ��������Ʈ�� ��Ʈ 
	Number* number = nullptr;
	Number* point = nullptr;
	Heart* heart = nullptr;

	UiSprite* score = nullptr;

	// ���� ���۽� ������ �ִϸ��̼�
	UiSprite* Start = nullptr;

	// ���� Ŭ����� ������ �ִϸ��̼�
	UiSprite* clear_ = nullptr;

	// ���� �� ���� �ִϸ��̼�
	UiSprite* Continue = nullptr;
	Number* ContinueNumber = nullptr;
	//bool IsFirstContinue = true;
	//bool IsFirstContinueDestroy = false;
	float ContinueTime = 5.0f;

	// Flash_Virus�� ����� Ÿ��.
	float FlashVirusTIme = 5.0f;

    // ���ѽð��� ���� 
	Number* time = nullptr;
	float ClearTime = 180.0f;

	// ���̷��� ������� �ѹ���
	bool IsFirstRevive = true;

	GameScene(int _stage);
	virtual void OnActiveScene() override;
	virtual void OnUpdate(float _deltaTime) override;
	virtual void OnFixedUpdate(float _fixedDeltaTime) override;
	virtual void OnRender() override;
	virtual void OnUiRender() override;
};
