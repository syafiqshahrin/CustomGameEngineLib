#pragma once
#include "ParticleAffector.h"

class NoiseAffector : public ParticleAffector
{
private:
	float m_Strength;
	Vector2 noise;
public:
	NoiseAffector(float s);
	void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) override;

};