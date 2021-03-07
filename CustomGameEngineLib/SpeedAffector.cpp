#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
#include "Curves.h"
#include "SpeedAffector.h"

SpeedAffector::SpeedAffector()
{
	SampleFromCurve = &Curves::easeInQuartWithInverseParabola;
}

void SpeedAffector::SetSampleCurveFunction(float(*CurveFunction)(float))
{
	SampleFromCurve = CurveFunction;
}

void SpeedAffector::AffectorParticleUpdate(ParticleObject* particle, float deltaTime)
{
	float time = 1.0f - (particle->m_currentLifetime / particle->m_Lifetime);
	
	float speed = SampleCurve(time);
	if (speed < 0)
	{
		speed = 0.0f;
	}
	particle->m_CurrentAcceleration = particle->m_Acceleration * (speed);
}

float SpeedAffector::SampleCurve(float t)
{
	float s = (*SampleFromCurve)(t);
	//std::cout << s << std::endl;
	return s;

}
