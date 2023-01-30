#pragma once

class PlayerInfo : public Singleton<PlayerInfo>
{
public:
	int score, hp;
	bool IsFirstContinue;
	bool IsFirstContinueDestroy;
};

static PlayerInfo playerInfo;

class Player : public Entity
{
public:

	Sprite ItemSprite[4];
	SpriteRI ItemSpriteRI[4];
	int curItem = 0;
	float ItemSpritePlayTime = 0.0f;

	bool NowNohit = false;
	bool IsDefense = false;
	bool first = true;
	float NoHitTime = 0.0f;

	float i_frame = 0.0f;

	// 플레이어는 GenerateMoveCollision ... 을 이용해 충돌 크기를 확장하면 안 됩니다.
	// 구현의 편의성을 위해 IsFrameMove 에 전부 넣었습니다. (하드코딩)
	virtual bool IsFrameMove(const FrameMoveCondition& _condition, FrameMoveResult& _result) override;
	virtual void OnFrameIntervalDirectionUpdate() override;
	virtual void OnDead() override;

	Player();
	void ItemAbility(float _ItemAnimationTime);
	void Cheating();
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void OnCollision(const CollisionBody& body) override {};
	virtual void Render() override;
};