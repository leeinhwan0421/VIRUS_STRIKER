#pragma once
class Virus_Flash : public Enemy
{
public:

	virtual void OnCollisionBoundary() override;

	// ������ ��� �Ƴ� �ȵƳ� �Ǵ�
	bool firstSpawn = true;
	// ���� �ð�
	float FlashTime = 1.5f;
	// ü���� ��������Ʈ
	bool changeSprite = false;

	float tarRotate = 60.0f;
	float curRotate = 0.0f;

	Virus_Flash();
	virtual void FixedUpdate(float _fixedDeltaTime) override;
};

