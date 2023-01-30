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

	// �� �ٱ��� ����� �� �˻��ϱ�
	BOOL IsOutBound(D3DXVECTOR2 _pos);

	// InfectionMap�� �ش� ��ġ ���� ��������
	D3DCOLOR GetPixel(D3DXVECTOR2 _pos);
	PixelState GetPixelState(D3DXVECTOR2 _pos);

	// BoundaryMap�� �ش� ��ġ ���� ��������
	D3DCOLOR GetBoundaryPixel(D3DXVECTOR2 _pos);
	BoundaryPixelState GetBoundaryPixelState(D3DXVECTOR2 _pos);

	// �̵� ��θ� �ʿ� ������Ʈ
	void UpdateMovePath(D3DXVECTOR2 _pos);
	void RemoveLastMovePath();

	// �̵� ��θ� �ʿ��� �����
	void ClearMovePath();

	// �̵� ��θ� ���� ���� ä��� �����ϱ�
	void CalcFloodFill();

	// �ش� PixelState ���� ���� �ȼ� ��ǥ�� �������� �ϳ� �����ɴϴ�.
	bool Random(PixelState _state, D3DXVECTOR2& _out);

	// �ش� BoundaryPixelState ���� ���� �ȼ� ��ǥ�� �������� �ϳ� �����ɴϴ�.
	bool Random(BoundaryPixelState _state, D3DXVECTOR2& _out);

	// �ش� Entity�� ��ȯ �� ������ ��ġ�� �����ɴϴ�.
	bool Random(PixelState _state, const Entity* _entity, D3DXVECTOR2& _out);

private:

	// ���� ä��� (��� �˰���)
	void FloodFill(D3DXVECTOR2 _pos);

	// ������ �������� (����ȯ����)
	void RandomSpawnOfItem(int A);

public:

	Map(int _stage);
	virtual void Update(float _deltaTime) override;
	virtual void LateUpdate(float _deltaTime) override;
	virtual void FixedUpdate(float _fixedDeltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(const CollisionBody& body) override;
};

