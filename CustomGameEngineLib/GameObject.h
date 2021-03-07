#pragma once
#include <list>
#include <iterator>
class Behavior;
class Input;
class Matrix4;
class Collider;
class GameObject
{
private:
	Sprite* m_Sprite;
	Vector3 m_Position;
	Vector3 m_Scale;
	float m_Rotation;
	Color m_Color;
	Blendmode m_Blend;
	bool enabled;
	std::list<Behavior*> attachedBehaviors;
	std::list <Behavior*>::iterator it;
	Matrix4 m_GameObjectMatrix;
	GameObject* parent;
	void UpdatePosMatrix();
	Collider* collider;
	bool colliderEnabled;
public:
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

	void SetParent(GameObject* par);
	Matrix4 GetMatrix();

	void AddBehavior(Behavior* behavior);
	void StartBehaviors();

	void EnableCollider();
	void DisableCollider();

	virtual void Update(float deltaTime, Input& inputData);
	virtual void Draw();

	Matrix4 translateMatrix;
	Matrix4 rotateMatrix;
};