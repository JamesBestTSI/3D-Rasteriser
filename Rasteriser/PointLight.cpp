#include "PointLight.h"


// Constructor
PointLight::PointLight()
{
	_Position = Vertex(0, 5, -3);

	ip_red = 255.0f;
	ip_green = 255.0f;
	ip_blue = 255.0f;

	coefficient_a = 0;
	coefficient_b = 1;
	coefficient_c = 0;
}

PointLight::PointLight(Vertex pos)
{
	_Position = pos;

	ip_red = 255.0f;
	ip_green = 255.0f;
	ip_blue = 255.0f;

	coefficient_a = 0;
	coefficient_b = 1;
	coefficient_c = 0;
}

PointLight::PointLight(Vertex pos, COLORREF colour)
{
	_Position = pos;

	ip_red = GetRValue(colour);
	ip_green = GetGValue(colour);
	ip_blue = GetBValue(colour);

	coefficient_a = 2;
	coefficient_b = 1;
	coefficient_c = 0;
}

// Deconstructor
PointLight::~PointLight()
{
}

// GET
Vertex PointLight::GetPos()
{
	return _Position;
}
float PointLight::GetRedIntensity()
{
	return ip_red;
}
float PointLight::GetBlueIntensity()
{
	return ip_blue;
}
float PointLight::GetGreenIntensity()
{
	return ip_green;
}

float PointLight::GetCoefficientA()
{
	return coefficient_a;
}

float PointLight::GetCoefficientB()
{
	return coefficient_b;
}

float PointLight::GetCoefficientC()
{
	return coefficient_c;
}

// SET
void PointLight::SetPos(Vertex pos)
{
	_Position = pos;
}
void PointLight::SetRedIntensity(float red)
{
	ip_red = red;
}
void PointLight::SetBlueIntensity(float blue)
{
	ip_blue = blue;
}
void PointLight::SetGreenIntensity(float green)
{
	ip_green = green;
}
