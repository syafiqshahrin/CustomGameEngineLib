#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
#include "SizeAffector.h"

SizeAffector::SizeAffector(float startSize, float endSize)
{
	m_StartSize = startSize;
	m_EndSize = endSize;
}

void SizeAffector::AffectorParticleUpdate(ParticleObject* particle, float deltaTime)
{
	float t = particle->m_currentLifetime / particle->m_Lifetime;

	Vector3 newScale;
	newScale.x = (m_EndSize * (1.0f - t)) + (m_StartSize * t);
	newScale.y = (m_EndSize* (1.0f - t)) + (m_StartSize * t);
	newScale.z = 1.0f;
	particle->SetScale(newScale);
}
