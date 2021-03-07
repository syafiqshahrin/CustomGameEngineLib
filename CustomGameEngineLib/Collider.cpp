#include "CoreHeaders.h"
#include "Collider.h"

void Collider::CalculateRadius()
{
	Vector2 dimension = gameObject->m_Sprite->m_Dimensions;
	Vector3 scale = gameObject->GetScale();
	float x = dimension.x * scale.x;
	float y = dimension.y * scale.y;
	if (x > y)
	{
		radius = x;
	}
	else
	{
		radius = y;
	}
}

Collider::Collider(GameObject* g)
{
	gameObject = g;
	InitialiseCollider();
	ColliderManager::AddCollider(this);
	
}

Collider::~Collider()
{
	ColliderManager::RemoveCollider(this);
}

void Collider::InitialiseCollider()
{
	m_PrevPosition = gameObject->GetPosition();
	CalculateRadius();
}

void Collider::CheckCollision()
{
	Vector3 currentPos = gameObject->GetPosition();
	for (std::list <Collider*>::iterator it = ColliderManager::instance->ActiveColliders.begin();
		it != ColliderManager::instance->ActiveColliders.end(); it++)
	{
		if ((*it) == this)
		{

			continue;
		}
		if (!((*it)->gameObject->colliderEnabled))
		{

			continue;
		}
		Vector3 curColliderPos = (*it)->gameObject->GetPosition();
		float cureColliderRad = (*it)->radius;
		Vector3 distanceVec = curColliderPos - currentPos;
		float distanceSqr = Vector3::lengthSquared(distanceVec);
		float safeRadius = (radius + cureColliderRad) * (radius + cureColliderRad);
		
		if (distanceSqr < safeRadius)
		{
			gameObject->SetPosition(m_PrevPosition);
		}
		
	}
	ColliderManager::instance->ActiveColliders.remove(this);
	m_PrevPosition = gameObject->GetPosition();
	
}

void Collider::Draw()
{

}


