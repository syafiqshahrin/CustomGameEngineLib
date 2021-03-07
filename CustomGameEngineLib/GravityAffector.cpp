#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
#include "GravityAffector.h"

GravityAffector::GravityAffector()
{
	m_Direction = Vector2(0.0f, -1.0f);
	m_Speed = 1.0f;
}

void GravityAffector::AffectorParticleUpdate(ParticleObject* particle, float deltaTime)
{
	Vector2 currentVelocity = particle->m_Velocity;
	Vector2 gravity = m_Direction * particle->m_CurrentAcceleration;
	currentVelocity.x += gravity.x;
	currentVelocity.y += gravity.y; 
	particle->m_Velocity = currentVelocity;
}

void GravityAffector::SetDirection(Vector2 dir)
{
	m_Direction = dir;
}

void GravityAffector::SetGravitySpeed(float speed)
{
	m_Speed = speed;
}
