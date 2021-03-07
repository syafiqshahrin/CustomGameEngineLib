
#include <glad/glad.h>
#include <glfw3.h>
#include "Input.h"
#include "Scene.h"
#include "Application.h"




Application::Application(Scene* s)
{
	scene = s;
}

Application::~Application()
{

}

void Application::Start()
{
	//scene = new Demo1();
	scene->LoadScene();
	scene->Start();
}

void Application::Update(float deltatime,  Input &inputData)
{
	scene->Update(deltatime, inputData);

}

void Application::Draw()
{
	//glClearColor(68.0f / 255.0f, 74.0f / 255.0f, 70.0f / 255.0f, 1.0f);
	//glClearColor(255.0f / 255.0f, 0.0f, 251.0f / 255.0f, 0.1f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->Draw();


}

