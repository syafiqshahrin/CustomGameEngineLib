#include <cstdlib>
#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
#include "NoiseAffector.h"

NoiseAffector::NoiseAffector(float s)
{
	m_Strength = s;
	//float x = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	//float y = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	noise = Vector2(0.0f, 0.0f);
}

void NoiseAffector::AffectorParticleUpdate(ParticleObject* particle, float deltaTime)
{
	float x = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	float y = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
	//std::cout << x << " " << y << std::endl;
	noise = Vector2(x, y);
	noise = Vector2::normalize(noise) * m_Strength;

	particle->m_Velocity.x += noise.x;
	particle->m_Velocity.y += noise.y;

}
