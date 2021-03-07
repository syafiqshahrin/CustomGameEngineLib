#include <cstdlib>
#define _USE_MATH_DEFINES
#include <math.h> 
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "CircleRingEmitterShape.h"

CircleRingEmitterShape::CircleRingEmitterShape(float r, float t)
{
	m_Radius = r;
	m_Thickness = t;
	m_MinAngle = 0.0f;
	m_MaxAngle = 360.0f;
}

Vector3 CircleRingEmitterShape::GetEmitterSpawnPosition(const Vector3& particleSystemPos)
{
	float angle = m_MinAngle + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_MaxAngle - (m_MinAngle))));
	angle *= (M_PI / 180.0f);
	float thickness = m_Radius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((m_Radius + m_Thickness) - (m_Radius))));
	Vector3 spawnPos = Vector3(cosf(angle) * (thickness) + particleSystemPos.x, sinf(angle) * (thickness) + particleSystemPos.y, 0.0f);
	
	return spawnPos;
}

void CircleRingEmitterShape::SetSpawnAngles(float min, float max)
{
	m_MinAngle = min;
	m_MaxAngle = max;
}

void CircleRingEmitterShape::SetRingRadius(float r)
{
	m_Radius = r;
}
