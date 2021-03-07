#pragma once
#include "EmitterShape.h"

class QuadEmitterShape : public EmitterShape
{
private:
	float m_Length;
	float m_width;
public:
	QuadEmitterShape(float l);
	QuadEmitterShape(float w, float l);
	Vector3 GetEmitterSpawnPosition(const Vector3& particleSystemPos) override;

};