#pragma once
#include "ParticleAffector.h"

class PulsingAffector : public ParticleAffector
{
private:
	float m_PulseRate;
	float time;
public:
	PulsingAffector(float r);
	void SetPulseRate(float rate);
	void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) override;
};