#include <iostream>
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
#include "ParticleAffector.h"
#include "EmitterShape.h"
#include "Input.h"
#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(Sprite* sprite)
{
	m_Sprite = sprite;
	m_Position = Vector3(0.0f, 0.0f, 0.0f);
	m_Rotation = 0.0f;
	m_EmissionAmount = 20; //hardcoded emission amount will need to refactor
	m_EmissionRate = 0.1f; //hardcoded emission rate will need to refactor
	m_EmissionTimer = m_EmissionRate;
	m_ParticleSpeed = 100.0f;
	m_ParticleLifetimeMin = 2.0f;
	m_ParticleLifetimeMax = 2.0f;
	velSet = false;
	UpdateMatrix();
}

ParticleSystem::ParticleSystem(Sprite* sprite, Vector3 pos)
{
	m_Sprite = sprite;
	m_Position = pos;
	m_Rotation = 0.0f;
	m_EmissionAmount = 20; //hardcoded emission amount will need to refactor
	m_EmissionRate = 0.1f; //hardcoded emission rate will need to refactor
	m_EmissionTimer = m_EmissionRate;
	m_ParticleSpeed = 100.0f;
	m_ParticleLifetimeMin = 2.0f;
	m_ParticleLifetimeMax = 2.0f;
	velSet = false;
	UpdateMatrix();
}

ParticleSystem::ParticleSystem(Sprite* sprite, Vector3 pos, GameObject* par)
{
	m_Sprite = sprite;
	m_Position = pos;
	m_Rotation = 0.0f;
	m_EmissionAmount = 20; //hardcoded emission amount will need to refactor
	m_EmissionRate = 0.1f; //hardcoded emission rate will need to refactor
	m_EmissionTimer = m_EmissionRate;
	m_ParticleSpeed = 100.0f;
	m_ParticleLifetimeMin = 2.0f;
	m_ParticleLifetimeMax = 2.0f;
	parent = par;
	velSet = false;
	UpdateMatrix();
}

ParticleSystem::~ParticleSystem()
{
	while (!m_ParticleList.empty())
	{
		delete m_ParticleList.front();
		m_ParticleList.pop_front();
	}

}

void ParticleSystem::Update(float deltaTime, Input& inputData)
{
	if (m_EmissionTimer <= 0.0f)
	{
		SpawnParticles();
		m_EmissionTimer = m_EmissionRate;
	}
	else
	{
		m_EmissionTimer -= deltaTime;
	}
	if (!m_ParticleList.empty())
	{
		for (it = m_ParticleList.begin(); it != m_ParticleList.end();)
		{
			(*it)->Update(deltaTime, inputData);
			//std::cout << (*it)->m_CurrentAcceleration << std::endl;
			if (affectorList.size() > 0)
			{
				for (affectorIt = affectorList.begin(); affectorIt != affectorList.end(); affectorIt++)
				{

					(*affectorIt)->AffectorParticleUpdate((*it), deltaTime);
				}

			}


			if ((*it)->m_currentLifetime <= 0.0f)
			{
				delete* it; //make sure to free dead ParticleObjects
				it = m_ParticleList.erase(it);
			}
			else
			{
				if (it != m_ParticleList.end())
					it++;
			}
		}
	}




}
	



void ParticleSystem::Draw()
{

	if (!m_ParticleList.empty())
	{

		for (it = m_ParticleList.begin(); it != m_ParticleList.end(); it++)
		{
			
			(*it)->Draw();
			
		}
	}
}

void ParticleSystem::AddAffector(ParticleAffector* affector)
{
	affectorList.push_back(affector);
}

void ParticleSystem::SetEmissionRate(float er)
{
	m_EmissionRate = er;
}

void ParticleSystem::SetEmissionAmount(int em)
{
	m_EmissionAmount = em;
}

void ParticleSystem::SetParticleSpeed(float s)
{
	m_ParticleSpeed = s;
}

void ParticleSystem::SetParticleInitialVelocty(Vector2 v)
{
	m_ParticleInitialVelocity = v;
	velSet = true;
}

void ParticleSystem::SetParticleLifetime(float tMin, float tMax)
{

	m_ParticleLifetimeMin = tMin;
	m_ParticleLifetimeMax = tMax;
}

void ParticleSystem::SetParticleSystemPosition(Vector3 pos)
{
	m_Position = pos;
	UpdateMatrix();
}

void ParticleSystem::SetParticleSystemRotation(float a)
{
	m_Rotation = a;
	UpdateMatrix();
}

Vector3 ParticleSystem::GetParticleSystemPosition()
{
	return m_Position;
}

float ParticleSystem::GetParticleSystemRotation()
{
	return m_Rotation;
}

void ParticleSystem::SetEmitterShape(EmitterShape* em)
{
	Emitter = em;
}

void ParticleSystem::SetParent(GameObject* par)
{
	parent = par;
	UpdateMatrix();
}

bool ParticleSystem::ParticleEmpty()
{
	return m_ParticleList.empty();
}

void ParticleSystem::SpawnParticles()
{
	for (int i = 0; i < m_EmissionAmount; i++)
	{
		ParticleObject* p = new ParticleObject(m_Sprite);
		
		if (Emitter != nullptr)
		{
			Vector3 pos = m_Position; 
			Matrix4 pcMatrix = m_Matrix;
			Matrix4 mat;
			if (parent != nullptr)
			{
				mat = parent->translateMatrix * parent->rotateMatrix;
				pcMatrix = mat * m_Matrix;
			}
			
			Vector3 spawnPos = Emitter->GetEmitterSpawnPosition(Vector3(0.0f, 0.0f, 0.0f));
			Vector4 newPos = pcMatrix * Vector4(spawnPos.x, spawnPos.y, spawnPos.z, 1.0f);
			//std::cout << newPos.x << " " << newPos.y << std::endl;
			spawnPos.x = newPos.x;
			spawnPos.y = newPos.y;
			spawnPos.z = newPos.z;
			p->SetPosition(spawnPos);
			
		}
		else
		{
			p->SetPosition(Vector3(m_Position.x, m_Position.y, 0.0f));
		}
		p->SetBlendmode(Blendmode::Additive);
		p->SetScale(Vector3(0.1f, 0.1f, 1.0f)); //need to refactor scale as its hardcoded
		InitParticle(p);
		m_ParticleList.push_back(p);
	}
}

void ParticleSystem::InitParticle(ParticleObject* particle)
{

	particle->SetLifeTime(RandomiseParticleLifetime()); 
	float x, y;
	if (velSet)
	{
		if (parent != nullptr)
		{
			Vector4 newPos = parent->translateMatrix * parent->rotateMatrix * Matrix4::invert(Matrix4::translate(Vector3(m_Position.x, m_Position.y, m_Position.z))) * Vector4(m_ParticleInitialVelocity.x, m_ParticleInitialVelocity.y, 0.0f, 0.0f);
			x = newPos.x;
			y = newPos.y;
		}
		else
		{
			x = m_ParticleInitialVelocity.x;
			y = m_ParticleInitialVelocity.y;
		}
	
	}
	else if (Emitter != nullptr)
	{
		
		Matrix4 pcMatrix = Matrix4::translate(Vector3(m_Position.x, m_Position.y, m_Position.z));
		Vector4 pos;
		Matrix4 mat;
		if (parent != nullptr)
		{
			mat = parent->translateMatrix * parent->rotateMatrix;
			//pcMatrix = mat * Matrix4::translate(Vector3(m_Position.x, m_Position.y, m_Position.z));
			pcMatrix = mat * Matrix4::invert(Matrix4::translate(Vector3(m_Position.x, m_Position.y, m_Position.z)));
			pos = pcMatrix * Vector4(m_Position.x, m_Position.y, m_Position.z, 0.0f);
			pos.x += parent->GetPosition().x;
			pos.y += parent->GetPosition().y;
			pos.z += parent->GetPosition().z;
		}
		else
		{
			pos = pcMatrix * Vector4(m_Position.x, m_Position.y, m_Position.z, 0.0f);
		}
	

		//std::cout << pos.x << " " << pos.y << std::endl;
		//std::cout << particle->GetPosition().x << " " << particle->GetPosition().y << std::endl;
		Vector3 newPos;
		newPos.x = pos.x;
		newPos.y = pos.y;
		newPos.z = pos.z;
		Vector3 vel = particle->GetPosition() - newPos;
		x = vel.x;
		y = vel.y;
	}
	else
	{
		
		x = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
		y = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	}

	
	particle->m_Velocity = Vector2::normalize(Vector2(x, y)) * m_ParticleSpeed;   //speed harcoded will need to change 
	particle->SetAcceleration(m_ParticleSpeed);

}

float ParticleSystem::RandomiseParticleLifetime()
{
	float newLifetime = m_ParticleLifetimeMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_ParticleLifetimeMax - (m_ParticleLifetimeMin))));;

	return newLifetime;
}

void ParticleSystem::UpdateMatrix()
{
	m_Matrix =
		Matrix4::translate(Vector3(m_Position.x, m_Position.y, 0.0f)) *
		Matrix4::rotate(m_Rotation, Vector3(0, 0, 1));
}
