#pragma once

class ParticleObject : public GameObject
{
public:
	ParticleObject(Sprite* sprite);
	~ParticleObject();
	Vector2 m_Velocity;
	float m_Acceleration;
	float m_CurrentAcceleration;
	float m_Lifetime;
	float m_currentLifetime;

	void Update(float deltaTime, Input& inputData) override;
	void SetLifeTime(float l);
	void SetAcceleration(float a);


private:

};