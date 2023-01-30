#pragma once

class Enemy : public Entity
{
public:

	virtual void OnFrameMove(const FrameMoveResult& _result) override;
	virtual bool IsFrameMove(const FrameMoveCondition& _condition, FrameMoveResult& _result) override;
	virtual void OnDead() override;

public:

	virtual void OnCollisionBoundary() = 0;

public:

	virtual ~Enemy() {}
	virtual void FixedUpdate(float _fixedDeltaTime);
	// virtual void Render() {}
};

