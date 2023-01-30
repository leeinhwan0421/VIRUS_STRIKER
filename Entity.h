#pragma once

/*
	�ʿ��� �����ϴ� ��� Entity�� ������ ���� ��Ģ�� ���մϴ�.
	***�� ĭ, �� ĭ, ���� ĭ ���� �̵� (�ȼ�) ó���� �����մϴ�. (OnFrameMove)
	***�ּ� Entity �� MinFrameInterval ��ŭ �������� �մϴ�.
	���� MinFrameInterval ���� ������ �����ϰ� ���� ��� OnFrameIntervalDirectionUpdate ���� �����ϰ�, frameIntervalDirectionUpdate ���� True�� �����ϼ���.
	���� Frame ���� �ȼ� �浹�� �����ϰ� ���� ��� OnFrameMove ���� �����ϼ���.
*/

class Entity : public Object
{
public:

	Sprite sprite;
	SpriteRI spriteRI;
	D3DXVECTOR2 moveDirection = { 0.0f, 0.0f };
	float moveLength = 0.0f;
	float moveSpeed = 200.0f;
	bool stairEvent = false;

	bool frameIntervalDirectionUpdate = false;
	float fMinFrameInterval = 1.0f;
	int MinFrameInterval = 1;

	// ������ ���� �ܰ����� �׸� �� �ֵ��� ó���Ͽ����ϴ�.
	std::vector<D3DXVECTOR2> moveCollisionOffsets = { { 0.0f, 0.0f } };
	void GenerateMoveCollisionCircle(int _radius);
	void GenerateMoveCollisionBox(int _minx, int _miny, int _maxx, int _maxy);

private:

	void FrameMove(const D3DXVECTOR2& _direction);

public:

	// �̵��� ������ ��� �ش� ����ü�� �����Ͱ� ������ �Ǿ� �����ϴ�.
	struct FrameMoveResult
	{
		D3DXVECTOR2 np = { 0.0f, 0.0f };
		std::vector<Map::BoundaryPixelState> bps;
		bool IsplayerDead = false;
	};
	virtual void OnFrameMove(const FrameMoveResult& _result) {}

	// ���� �̵��� ���� �Ǻ��ϸ鼭 ������ ���� ��� ���� ó���� ���� ����� �����մϴ�.
	struct FrameMoveCondition
	{
		// Current Position Boundary Pixel State
		Map::BoundaryPixelState cpbps;
		// Current Position Pixel State
		Map::PixelState cpps;
		// Next Position Boundary Pixel State
		Map::BoundaryPixelState npbps;
		// Next Position Pixel State
		Map::PixelState npps;
		// Next Position
		D3DXVECTOR2 np;
	};
	virtual bool IsFrameMove(const FrameMoveCondition& _condition, FrameMoveResult& _result) { return false; }

	virtual void OnFrameIntervalDirectionUpdate() {}
	virtual void OnDead() {}

public:


	Entity() {};
	virtual ~Entity() {}
	virtual void Update(float _deltaTime) {};
	virtual void LateUpdate(float _deltaTime) {};
	virtual void FixedUpdate(float _fixedDeltaTime);
	virtual void Render();
	virtual void OnCollision(const CollisionBody& body);
};

