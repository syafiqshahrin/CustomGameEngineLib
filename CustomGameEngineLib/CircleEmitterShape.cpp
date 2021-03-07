#include <cstdlib>
#define _USE_MATH_DEFINES
#include <math.h> 
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "CircleEmitterShape.h"

CircleEmitterShape::CircleEmitterShape(float r)
{
	m_Radius = r;
	m_MinAngle = 0.0f;
	m_MaxAngle = 360.0f;
}

Vector3 CircleEmitterShape::GetEmitterSpawnPosition(const Vector3& particleSystemPos)
{
	float angle = m_MinAngle + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_MaxAngle - (m_MinAngle))));
	angle *= (M_PI / 180.0f);
	float ranRadius = 0.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_Radius - (0.0f))));
	float x = (particleSystemPos.x - m_Radius) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((particleSystemPos.x + m_Radius) - ((particleSystemPos.x - m_Radius)))));
	float y = (particleSystemPos.y - m_Radius) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((particleSystemPos.y + m_Radius) - ((particleSystemPos.y - m_Radius)))));
	Vector3 spawnPos = Vector3(cosf(angle) * ranRadius + particleSystemPos.x, sinf(angle) * ranRadius + particleSystemPos.y, 0.0f);
	
	return spawnPos;
}

void CircleEmitterShape::SetSpawnAngles(float min, float max)
{
	m_MinAngle = min;
	m_MaxAngle = max;
}

