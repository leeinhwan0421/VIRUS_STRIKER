#pragma once

class Boss : public Enemy
{
public:

	float tarRotate = 0.0f;
	float curRotate = 0.0f;

	virtual void OnCollisionBoundary() override;

	Boss();
	virtual void FixedUpdate(float _fixedDeltaTime) override;

};

