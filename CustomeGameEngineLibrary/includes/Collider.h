#pragma once


class GameObject;
struct CollisionData
{
public:
	CollisionData();
	CollisionData(bool h, GameObject* go);
	bool hit;
	GameObject* gameObjectHit;
};

class Collider
{
private:
	GameObject* gameObject;
	Vector3 m_PrevPosition;
	float radius;
	bool isTrigger;
	
public:
	Collider(GameObject* g);
	~Collider();

	void InitialiseCollider();
	void Draw();
	CollisionData CheckCollision();
	void CalculateRadius();
	void SetRadius(float r);
	void SetIsTrigger(bool s);
};

