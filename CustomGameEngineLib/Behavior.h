#pragma once
class GameObject;
class Input;
class Behavior
{
public:
	GameObject* gameObject;
	virtual void Start() = 0;
	virtual void Update(float deltaTime, Input& inputData) = 0;
	virtual void Draw() = 0;
};