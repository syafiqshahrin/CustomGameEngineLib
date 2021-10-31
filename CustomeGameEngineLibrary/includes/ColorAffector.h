#pragma once
#include "ParticleAffector.h"

class ColorAffector : public ParticleAffector
{
public:
	Color color1;
	Color color2;
	ColorAffector(const Color& c1, const Color& c2);
	void SetColor(const Color& c1, const Color& c2);
	void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) override;
};