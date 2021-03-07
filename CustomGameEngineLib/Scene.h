#pragma once

class Scene
{
public:
	virtual void Update(float deltaTime, Input &inputData) = 0;
	virtual void Draw() = 0;
	virtual void Start() = 0;
	virtual void LoadScene() = 0;
};