#pragma once

class Entity;
class Map : public Object
{
public:

	enum class PixelState
	{
		CLOSE,
		OPEN,
		COUNT
	};
	static constexpr D3DCOLOR colors[static_cast<int>(PixelState::COUNT)] = { 
		D3DCOLOR_ARGB(255, 255, 255, 255),
		D3DCOLOR_ARGB(0, 0, 0, 0)
	};
	enum class BoundaryPixelState
	{
		NONE,
		BOUNDARY,
		BOUNDARYEND,
		MOVEPATH,
		ENEMY,
		OBSTACLE,
		COUNT
	};
	static constexpr D3DCOLOR boundaryColors[static_cast<int>(BoundaryPixelState::COUNT)] = {
		D3DCOLOR_ARGB(0, 0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255),
		D3DCOLOR_ARGB(255, 0, 0, 0),
		D3DCOLOR_ARGB(255, 0, 0, 255),
		D3DCOLOR_ARGB(1, 0, 0, 0),
		D3DCOLOR_ARGB(255, 30, 30, 30)
	};
	bool isFloodFill = false;
	int mapWidth = 0, mapHeight = 0;
	Sprite spriteCureChangeMap;
	Sprite spriteCureMap;
	Sprite spriteInfectionMap;
	Sprite spriteBoundaryMap;
	SpriteRI spriteRI;
	std::vector<POINT> movePath;
	static constexpr POINT DirectionWay4[] = { POINT { 0, 1 }, POINT { 1, 0 }, POINT { 0, -1 }, POINT { -1, 0 } };
	static constexpr POINT DirectionWay8[] = { POINT { 0, 1 }, POINT { 1, 0 }, POINT { 0, -1 }, POINT { -1, 0 }, POINT { 1, 1 }, POINT { -1, 1 }, POINT { 1, -1 }, POINT { -1, -1 } };

	std::random_device randomDevice;
	int szPixel = 0;
	int szFillPixel = 0;

public:

	// 맵 바깥을 벗어났는 지 검사하기
	BOOL IsOutBound(D3DXVECTOR2 _pos);

	// InfectionMap의 해당 위치 정보 가져오기
	D3DCOLOR GetPixel(D3DXVECTOR2 _pos);
	PixelState GetPixelState(D3DXVECTOR2 _pos);

	// BoundaryMap의 해당 위치 정보 가져오기
	D3DCOLOR GetBoundaryPixel(D3DXVECTOR2 _pos);
	BoundaryPixelState GetBoundaryPixelState(D3DXVECTOR2 _pos);

	// 이동 경로를 맵에 업데이트
	void UpdateMovePath(D3DXVECTOR2 _pos);
	void RemoveLastMovePath();

	// 이동 경로를 맵에서 지우기
	void ClearMovePath();

	// 이동 경로를 토대로 색깔 채우기 진행하기
	void CalcFloodFill();

	// 해당 PixelState 값을 지닌 픽셀 좌표를 랜덤으로 하나 가져옵니다.
	bool Random(PixelState _state, D3DXVECTOR2& _out);

	// 해당 BoundaryPixelState 값을 지닌 픽셀 좌표를 랜덤으로 하나 가져옵니다.
	bool Random(BoundaryPixelState _state, D3DXVECTOR2& _out);

	// 해당 Entity가 소환 될 랜덤한 위치를 가져옵니다.
	bool Random(PixelState _state, const Entity* _entity, D3DXVECTOR2& _out);

private:

	// 색깔 채우기 (산불 알고리즘)
	void FloodFill(D3DXVECTOR2 _pos);

	// 아이템 랜덤생성 (이인환제작)
	void RandomSpawnOfItem(int A);

public:

	Map(int _stage);
	virtual void Update(float _deltaTime) override;
	virtual void LateUpdate(float _deltaTime) override;
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(const CollisionBody& body) override;
};

