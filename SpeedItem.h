#pragma once

class SpeedItem : public Item
{
public:

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	SpeedItem();
	virtual void FixedUpdate(float _fixedDeltaTime) override;

	// Enemy을(를) 통해 상속됨
	virtual void OnCollisionBoundary() override;
};

