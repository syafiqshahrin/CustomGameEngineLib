#pragma once
#include <list>
#include <iterator>

class ParticleSystem
{
public:
	ParticleSystem(Sprite* sprite);
	ParticleSystem(Sprite* sprite, Vector3 pos);
	ParticleSystem(Sprite* sprite, Vector3 pos, GameObject* par);
	~ParticleSystem();
	void Update(float deltaTime, Input& inputData);
	void Draw();
	void AddAffector(ParticleAffector* affector);
	void SetEmissionRate(float er);
	void SetEmissionAmount(int em);
	void SetParticleSpeed(float s);
	void SetParticleInitialVelocty(Vector2 v);
	void SetParticleLifetime(float tMin, float tMax);
	void SetParticleSystemPosition(Vector3 pos);
	void SetParticleSystemRotation(float a);
	Vector3 GetParticleSystemPosition();
	float GetParticleSystemRotation();
	void SetEmitterShape(EmitterShape* em);
	void SetParent(GameObject* par);
	bool ParticleEmpty();
	
private:
	GameObject* parent;
	std::list<ParticleObject*> m_ParticleList;
	std::list <ParticleObject*>::iterator it;
	EmitterShape* Emitter;
	float m_EmissionRate;
	int m_EmissionAmount;
	float m_EmissionTimer;
	float m_ParticleSpeed;
	float m_ParticleLifetimeMin;
	float m_ParticleLifetimeMax;
	Vector2 m_ParticleInitialVelocity;
	bool velSet;
	Vector3 m_Position;
	float m_Rotation;
	Matrix4 m_Matrix;
	Sprite* m_Sprite;
	//affectorList
	std::list<ParticleAffector*> affectorList;
	std::list <ParticleAffector*>::iterator affectorIt;
	void SpawnParticles();
	void InitParticle(ParticleObject* particle);
	float RandomiseParticleLifetime(); 
	void UpdateMatrix();
};