#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"

ParticleObject::ParticleObject(Sprite* sprite) : GameObject(sprite)
{
	m_Lifetime = 0.0f;
	m_currentLifetime = m_Lifetime;
}

ParticleObject::~ParticleObject()
{
	//std::cout << "Particle destructed" << std::endl;
}

void ParticleObject::Update(float deltaTime, Input& inputData)
{
	Vector3 currentPos = GetPosition();
	Vector3 newPos = currentPos;
	
	if (Vector2::lengthSquared(m_Velocity) > (m_CurrentAcceleration * m_CurrentAcceleration))
	{
		m_Velocity = Vector2::normalize(m_Velocity) * m_CurrentAcceleration;
	}
	
	newPos.x += m_Velocity.x * deltaTime;
	newPos.y += m_Velocity.y * deltaTime;
	SetPosition(newPos);
	
	m_currentLifetime -= deltaTime;
}

void ParticleObject::SetLifeTime(float l)
{
	m_Lifetime = l;
	m_currentLifetime = m_Lifetime;
}
void ParticleObject::SetAcceleration(float a)
{
	m_Acceleration = a;
	m_CurrentAcceleration = m_Acceleration;
}