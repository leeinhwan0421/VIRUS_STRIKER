#pragma once

class Object;
class CollisionBody
{
public:

	struct Circle
	{
		float radius = 0.0f;
	};
	Circle circle;
	struct AABB
	{
		D3DXVECTOR2 min = {};
		D3DXVECTOR2 max = {};
	};
	AABB aabb;
	Object* owner = nullptr;
	CollisionBody(Object* _owner);
};
extern bool IsCollision(const CollisionBody& lhs, const CollisionBody& rhs);

class Object
{
public:

	D3DXVECTOR2 pos = { 0.0f, 0.0f };
	int collisionLayer = 0;
	int layer = 0;
	bool destroy = false;
	std::wstring tag = TEXT("");
	std::vector<CollisionBody> bodies;

	virtual ~Object() {};
	virtual void Update(float _deltaTime) = 0;
	virtual void LateUpdate(float _deltaTime) = 0;
	virtual void FixedUpdate(float _fixedDeltaTime) = 0;
	virtual void Render() = 0;
	virtual void OnCollision(const CollisionBody& body) = 0;
	void RenderDebug();

};

class ObjectManager
{
private:

	std::vector<Object*> addObjects, objects;

public:

	void AddObject(Object* newObject);
	void Update(float _deltaTime);
	void FixedUpdate(float _fixedDeltaTime);
	void Render();
};