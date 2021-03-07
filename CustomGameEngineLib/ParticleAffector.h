#pragma once
class ParticleObject;
class ParticleAffector
{
public:
	//gravity over time
	//color over time 
	//size over time
	//alpha over time
	//at least 4 affectors
	virtual void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) = 0;
};