#pragma once

class Virus_Big : public Enemy
{
public:

	virtual void OnCollisionBoundary() override;

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	Virus_Big();
	virtual void FixedUpdate(float _fixedDeltaTime) override;
};


