#pragma once

class SpeedItem : public Item
{
public:

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	SpeedItem();
	virtual void FixedUpdate(float _fixedDeltaTime) override;

	// Enemy��(��) ���� ��ӵ�
	virtual void OnCollisionBoundary() override;
};

