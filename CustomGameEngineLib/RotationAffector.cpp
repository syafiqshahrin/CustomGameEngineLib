#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
#include "RotationAffector.h"

RotationAffector::RotationAffector(float s)
{
	m_RotationSpeed = s;
}

void RotationAffector::AffectorParticleUpdate(ParticleObject* particle, float deltaTime)
{
	particle->SetRotation(particle->GetRotation() + (deltaTime * m_RotationSpeed));
}

void RotationAffector::SetRotationSpeed(float s)
{
	m_RotationSpeed = s;
}
