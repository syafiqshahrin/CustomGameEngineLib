#include "Curves.h"

float Curves::easeInQuartWithInverseParabola(float t)
{
	float a = 1 - pow(t, 5.0f);
	float b = pow((-1.0f - (-1.0f * t) * 2.0f), 2.0f) * -1 + 1.0f;
	//std::cout << s/b << std::endl;
	return (-1 * (b / a) + 1.045f) * 2;
}
