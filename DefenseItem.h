#pragma once

class DefenseItem : public Item
{
public:

	int Itemcord = 1;

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	DefenseItem();
	virtual void FixedUpdate(float _fixedDeltaTime) override;

	// Enemy��(��) ���� ��ӵ�
	virtual void OnCollisionBoundary() override;
};

