#include "Header.h"

CollisionBody::CollisionBody(Object* _owner) : owner(_owner)
{
}

bool IsCollision(const CollisionBody& lhs, const CollisionBody& rhs)
{
	D3DXVECTOR2 dp = lhs.owner->pos - rhs.owner->pos;
	float dl = D3DXVec2Length(&dp);
	if (dl < lhs.circle.radius + rhs.circle.radius)
		return true;

	D3DXVECTOR2 min1 = lhs.owner->pos + lhs.aabb.min;
	D3DXVECTOR2 max1 = lhs.owner->pos + lhs.aabb.max;
	D3DXVECTOR2 min2 = rhs.owner->pos + rhs.aabb.min;
	D3DXVECTOR2 max2 = rhs.owner->pos + rhs.aabb.max;
	if (max1.x > min2.x && max1.y > min2.y &&
		max2.x > min1.x && max2.y > min1.y)
		return true;

	return false;
}

void Object::RenderDebug()
{
#if defined (_DEBUG)
	for (const auto& body : bodies)
	{
		if (body.circle.radius != 0.0f)
		{
			D3DXVECTOR3 lines[37] = {};
			for (int i = 0; i < 37; ++i)
			{
				D3DXVECTOR2 vp = MathUtility::DegreeToVector2(i * body.circle.radius) + body.owner->pos;
				lines[i] = D3DXVECTOR3(vp.x, vp.y, 0.0f);
			}
			D3DXMATRIX matrix = Direct3D::GetInstance().matView * Direct3D::GetInstance().matProj;
			Direct3D::GetInstance().pLine->DrawTransform(lines, 37, &matrix, D3DCOLOR_ARGB(255, 255, 0, 0));
		}

		if (body.aabb.min != D3DXVECTOR2{ 0.0f, 0.0f } && body.aabb.max != D3DXVECTOR2{ 0.0f, 0.0f })
		{
			D3DXVECTOR2 minp = body.aabb.min + body.owner->pos;
			D3DXVECTOR2 maxp = body.aabb.max + body.owner->pos;
			D3DXVECTOR3 lines[5] = {
				{minp.x, minp.y, 0.0f},
				{minp.x, maxp.y, 0.0f},
				{maxp.x, maxp.y, 0.0f},
				{maxp.x, minp.y, 0.0f},
				{minp.x, minp.y, 0.0f}
			};
			D3DXMATRIX matrix = Direct3D::GetInstance().matView * Direct3D::GetInstance().matProj;
			Direct3D::GetInstance().pLine->DrawTransform(lines, 5, &matrix, D3DCOLOR_ARGB(255, 255, 0, 0));
		}
	}
#endif
}

void ObjectManager::AddObject(Object* newObject)
{
	addObjects.push_back(newObject);
}

void ObjectManager::Update(float _deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();
	std::sort(objects.begin(), objects.end(), [](const Object* lhs, const Object* rhs) 
	{ 
		return lhs->layer < rhs->layer;
	});
	for (auto object : objects)
	{
		object->Update(_deltaTime);
	}
	for (auto object : objects)
	{
		object->LateUpdate(_deltaTime);
	}
}

void ObjectManager::FixedUpdate(float _fixedDeltaTime)
{
	for (auto it = objects.begin(); it != objects.end(); )
	{
		(*it)->FixedUpdate(_fixedDeltaTime);
		if ((*it)->destroy)
		{
			delete* it;
			it = objects.erase(it);
		}
		else
			++it;
	}

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if ((*it)->collisionLayer == 0) continue;
		for (auto it2 = it + 1; it2 != objects.end(); ++it2)
		{
			if ((*it)->collisionLayer != (*it2)->collisionLayer) continue;
			for (auto& body : (*it)->bodies)
			{
				for (auto& body2 : (*it2)->bodies)
				{
					if (IsCollision(body, body2))
					{
						(*it)->OnCollision(body2);
						(*it2)->OnCollision(body);
					}
				}
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto object : objects)
	{
		object->Render();
		object->RenderDebug();
	}
}
