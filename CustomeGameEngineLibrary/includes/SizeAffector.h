#pragma once
#include "ParticleAffector.h"
class SizeAffector : public ParticleAffector
{
private:
	float m_StartSize;
	float m_EndSize;
public:
	SizeAffector(float startSize, float endSize);
	void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) override;
};