#pragma once
#include "ParticleAffector.h"

class GravityAffector : public ParticleAffector
{
private:
	Vector2 m_Direction;
	float m_Speed;
public:
	//set gravity direction
	//set strenght of gravity
	GravityAffector();
	void AffectorParticleUpdate(ParticleObject* particle, float deltaTime) override;
	void SetDirection(Vector2 dir);
	void SetGravitySpeed(float speed);
};