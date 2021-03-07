#include <cstdlib>
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "QuadEmitterShape.h"

QuadEmitterShape::QuadEmitterShape(float l)
{
	m_Length = l;
	m_width = l;
}

QuadEmitterShape::QuadEmitterShape(float w, float l)
{
	m_Length = l;
	m_width = w;
}

Vector3 QuadEmitterShape::GetEmitterSpawnPosition(const Vector3& particleSystemPos)
{
	float x = (particleSystemPos.x - m_width) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((particleSystemPos.x + m_width) - ((particleSystemPos.x - m_width)))));
	float y = (particleSystemPos.y - m_Length) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((particleSystemPos.y + m_Length) - ((particleSystemPos.y - m_Length)))));
	Vector3 spawnPos = Vector3(x, y, 0.0f);
	return spawnPos;
}
