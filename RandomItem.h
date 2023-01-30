#pragma once

class RandomItem : public Item
{
public:

	int Itemcord = 0;
	float ItemSpritePlayTimeArray[4] = { 180.0f,1.0f,180.0f,4.0f };

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	RandomItem();
	virtual void FixedUpdate(float _fixedDeltaTime) override;

	// Enemy을(를) 통해 상속됨
	virtual void OnCollisionBoundary() override;
};

