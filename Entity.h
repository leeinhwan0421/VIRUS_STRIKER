#pragma once

/*
	맵에서 동작하는 모든 Entity는 다음과 같은 규칙을 지닙니다.
	***한 칸, 한 칸, 각각 칸 별로 이동 (픽셀) 처리를 진행합니다. (OnFrameMove)
	***최소 Entity 는 MinFrameInterval 만큼 움직여야 합니다.
	각각 MinFrameInterval 마다 방향을 갱신하고 싶은 경우 OnFrameIntervalDirectionUpdate 에서 진행하고, frameIntervalDirectionUpdate 값을 True로 변경하세요.
	각각 Frame 마다 픽셀 충돌을 진행하고 싶은 경우 OnFrameMove 에서 진행하세요.
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

	// 성능을 위해 외곽선만 그릴 수 있도록 처리하였습니다.
	std::vector<D3DXVECTOR2> moveCollisionOffsets = { { 0.0f, 0.0f } };
	void GenerateMoveCollisionCircle(int _radius);
	void GenerateMoveCollisionBox(int _minx, int _miny, int _maxx, int _maxy);

private:

	void FrameMove(const D3DXVECTOR2& _direction);

public:

	// 이동에 성공한 경우 해당 구조체에 데이터가 저장이 되어 남습니다.
	struct FrameMoveResult
	{
		D3DXVECTOR2 np = { 0.0f, 0.0f };
		std::vector<Map::BoundaryPixelState> bps;
		bool IsplayerDead = false;
	};
	virtual void OnFrameMove(const FrameMoveResult& _result) {}

	// 각각 이동에 대해 판별하면서 문제가 없을 경우 추후 처리를 위해 결과를 저장합니다.
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

