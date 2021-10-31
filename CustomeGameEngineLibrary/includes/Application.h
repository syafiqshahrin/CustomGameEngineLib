#pragma once


class Scene;
class Application
{
private:
	
	Scene* scene;

public:
	Application(Scene* scene);
	~Application();
	void Start();
	void Update(float deltaTime, Input &inputData);
	void Draw();
};
