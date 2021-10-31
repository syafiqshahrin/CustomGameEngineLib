#include "Curves.h"

float Curves::easeInQuartWithInverseParabola(float t)
{
	float a = 1 - pow(t, 5.0f);
	float b = pow((-1.0f - (-1.0f * t) * 2.0f), 2.0f) * -1 + 1.0f;
	//std::cout << s/b << std::endl;
	return (-1 * (b / a) + 1.045f) * 2;
}
float Curves::easeInOutExpo(float t){
	float val;
	if (t == 0.0f)
	{
		val = 0;
	}
	else if (t == 1.0f)
	{
		val = 1;
	}
	else if (t < 0.5f)
	{
		val = pow(2.0f, 20.0f * t - 10.0f) / 2.0f;
	}
	else if (t > 0.5f)
	{
		val = (2.0f - pow(2.0f, -20.0f * t + 10.0f)) / 2.0f;
	}
	return val;

}