#pragma once

class Collider
{
private:
	GameObject* gameObject;
	Vector3 m_PrevPosition;
	float radius;
	
	
public:
	Collider(GameObject* g);
	~Collider();

	void InitialiseCollider();
	void Draw();
	void CheckCollision();
	void CalculateRadius();
};