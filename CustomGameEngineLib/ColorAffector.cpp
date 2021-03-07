#include <glad/glad.h>
#include <glfw3.h>
#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleObject.h"
//#include "ParticleAffector.h"
#include "ColorAffector.h"

ColorAffector::ColorAffector(const Color& c1, const Color& c2)
{
	color1 = c1; 
	color2 = c2;
}

void ColorAffector::SetColor(const Color& c1, const Color& c2)
{
	color1 = c1;
	color2 = c2;
}

void ColorAffector::AffectorParticleUpdate(ParticleObject* particle, float deltaTime)
{
	Color mixColor;
	float a = particle->m_currentLifetime / particle->m_Lifetime;
	
	mixColor.r = (color2.r * (1.0f - a)) + (color1.r * a);
	mixColor.g = (color2.g * (1.0f - a)) + (color1.g * a);
	mixColor.b = (color2.b * (1.0f - a)) + (color1.b * a);
	mixColor.a = (color2.a * (1.0f - a)) + (color1.a * a);
	//std::cout << "r: " << mixColor.r << " g: " << mixColor.g << " b: " << mixColor.b << std::endl;
	particle->SetColor(mixColor);

}
