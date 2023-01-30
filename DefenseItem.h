#pragma once

class DefenseItem : public Item
{
public:

	int Itemcord = 1;

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	DefenseItem();
	virtual void FixedUpdate(float _fixedDeltaTime) override;

	// Enemy을(를) 통해 상속됨
	virtual void OnCollisionBoundary() override;
};

