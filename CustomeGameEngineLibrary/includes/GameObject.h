#pragma once
#include <list>
#include <iterator>
#include "Collider.h"
class Behavior;
class Input;
class Matrix4;
//struct CollisionData;
//class Collider;

class GameObject
{
private:
	//Sprite* m_Sprite;
	Vector3 m_Position;
	Vector3 m_Scale;
	float m_Rotation;
	Color m_Color;
	Blendmode m_Blend;
	bool enabled;
	bool drawEnabled;
	std::list<Behavior*> attachedBehaviors;
	std::list <Behavior*>::iterator it;
	Matrix4 m_GameObjectMatrix;
	GameObject* parent;
	void UpdatePosMatrix();
	Collider* collider;
	bool colliderEnabled;
	CollisionData collisionData;
public:

	Sprite* m_Sprite;

	GameObject();
	~GameObject();
	GameObject(Sprite* sprite);
	GameObject(Sprite* sprite, Vector3 pos);
	GameObject(Sprite* sprite, Vector3 pos, GameObject* par);
	friend class Collider;
	void SetPosition(Vector3 pos);
	Vector3 GetPosition();

	void SetScale(Vector3 scale);
	Vector3 GetScale();

	void SetRotation(float rad);
	float GetRotation();

	void SetColor(Color col);
	Color GetColor();

	void SetBlendmode(Blendmode mode);
	Blendmode GetBlendmode();

	void SetEnable(bool e);
	bool GetEnabled();

	void SetDrawEnable(bool e);
	bool GetDrawEnabled();

	void SetParent(GameObject* par);
	Matrix4 GetMatrix();

	void AddBehavior(Behavior* behavior);
	void StartBehaviors();

	void EnableCollider();
	void DisableCollider();
	Collider* GetCollider();
	CollisionData CheckCollision();

	virtual void Update(float deltaTime, Input& inputData);
	virtual void Draw();
	template <typename T>
	T* GetBehavior()
	{
		T* behavior = nullptr;
		if (!attachedBehaviors.empty())
		{
			for (it = attachedBehaviors.begin(); it != attachedBehaviors.end(); it++)
			{
				if (dynamic_cast<T*>((*it)) != nullptr)
				{
					behavior = dynamic_cast<T*>(*it);
					return behavior;
				}

			}
		}
		return behavior;
	}

	Matrix4 translateMatrix;
	Matrix4 rotateMatrix;
};