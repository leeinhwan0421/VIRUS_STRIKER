#pragma once
class Virus_Flash : public Enemy
{
public:

	virtual void OnCollisionBoundary() override;

	// 스폰이 방금 됐나 안됐나 판단
	bool firstSpawn = true;
	// 점멸 시간
	float FlashTime = 1.5f;
	// 체인지 스프라이트
	bool changeSprite = false;

	float tarRotate = 60.0f;
	float curRotate = 0.0f;

	Virus_Flash();
	virtual void FixedUpdate(float _fixedDeltaTime) override;
};

