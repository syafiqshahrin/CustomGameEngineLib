#pragma once

class ColliderManager
{
private:
	ColliderManager();
	static ColliderManager* instance;
	std::list<Collider*> AllColliders;
	std::list<Collider*> ActiveColliders;
public:
	friend class Collider;
	static void RemoveCollider(Collider* col);
	static void AddCollider(Collider* col);
	static void UpdateActiveColliders();

};
