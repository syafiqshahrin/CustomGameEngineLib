#include <cstdlib>
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
#include "PulsingAffector.h"

PulsingAffector::PulsingAffector(float r)
{
	m_PulseRate = r;

}

void PulsingAffector::SetPulseRate(float rate)
{
	m_PulseRate = rate;
}

void PulsingAffector::AffectorParticleUpdate(ParticleObject* particle, float deltaTime)
{
	float t = particle->m_currentLifetime;
	float pulse = sinf((t += deltaTime) * m_PulseRate) * 0.5f + 0.5f;
	particle->SetScale(particle->GetScale() * pulse);

}

