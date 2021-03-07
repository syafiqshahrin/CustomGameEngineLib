#pragma once
#include "EmitterShape.h"

class CircleRingEmitterShape : public EmitterShape
{
private:
	float m_Radius;
	float m_Thickness;
	float m_MinAngle;
	float m_MaxAngle;
public:
	CircleRingEmitterShape(float r, float t);
	void SetRingRadius(float r);
	Vector3 GetEmitterSpawnPosition(const Vector3& particleSystemPos) override;
	void SetSpawnAngles(float min, float max);
};