#pragma once

class HealItem : public Item
{
public:

	int Itemcord = 2;

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	HealItem();
	virtual void FixedUpdate(float _fixedDeltaTime) override;

	// Enemy��(��) ���� ��ӵ�
	virtual void OnCollisionBoundary() override;
};

