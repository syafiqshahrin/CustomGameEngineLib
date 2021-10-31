#pragma once
#include "EmitterShape.h"

class CircleEmitterShape : public EmitterShape
{
private:
	float m_Radius;
	float m_MinAngle;
	float m_MaxAngle;
public:
	CircleEmitterShape(float r);
	Vector3 GetEmitterSpawnPosition(const Vector3& particleSystemPos) override;
	void SetSpawnAngles(float min, float max);
};