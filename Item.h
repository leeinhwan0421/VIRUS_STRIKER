#pragma once

class Item : public Entity
{
public:

	virtual bool IsFrameMove(const FrameMoveCondition& _condition, FrameMoveResult& _result) override;
	virtual void OnDead() override;

public:

	virtual void OnCollisionBoundary() = 0;

public:

	virtual ~Item() {}
	virtual void FixedUpdate(float _fixedDeltaTime);
	// virtual void Render() {}
};

