#include "DirectionalLight.h"


// Constructor
DirectionalLight::DirectionalLight()
{
	Direction = Vector3D(0, 5, -3);

	id_red = 255.0f;
	id_green = 255.0f;
	id_blue = 255.0f;
}

DirectionalLight::DirectionalLight(Vector3D direction)
{
	Direction = direction;

	id_red = 255.0f;
	id_green = 255.0f;
	id_blue = 255.0f;
}

DirectionalLight::DirectionalLight(Vector3D direction, COLORREF colour)
{
	Direction = direction;

	id_red = GetRValue(colour);
	id_green = GetGValue(colour);
	id_blue = GetBValue(colour);
}

// Deconstructor
DirectionalLight::~DirectionalLight()
{
}

// GET
Vector3D DirectionalLight::GetDirection()
{
	return Direction;
}
float DirectionalLight::GetRedIntensity()
{
	return id_red;
}
float DirectionalLight::GetBlueIntensity()
{
	return id_blue;
}
float DirectionalLight::GetGreenIntensity()
{
	return id_green;
}

// SET
void DirectionalLight::SetDirection(Vector3D direction)
{
	Direction = direction;
}
void DirectionalLight::SetRedIntensity(float red)
{
	id_red = red;
}
void DirectionalLight::SetBlueIntensity(float blue)
{
	id_blue = blue;
}
void DirectionalLight::SetGreenIntensity(float green)
{
	id_green = green;
}
