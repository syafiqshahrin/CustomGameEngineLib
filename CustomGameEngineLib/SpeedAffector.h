#pragma once
#include "ParticleAffector.h"
class Curves;
class SpeedAffector : public ParticleAffector
{
private:
	float (*SampleFromCurve)(float) = nullptr;
public:
	SpeedAffector();
	void SetSampleCurveFunction(float (*CurveFunction)(float));
	void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) override;
	float SampleCurve(float t);
	
};