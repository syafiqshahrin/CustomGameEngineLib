#pragma once
#include "ParticleAffector.h"

class RotationAffector : public ParticleAffector
{
private:
	float m_RotationSpeed;
public:
	RotationAffector(float s);
	void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) override;
	void SetRotationSpeed(float s);

};