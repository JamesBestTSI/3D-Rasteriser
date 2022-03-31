#include "AmbientLight.h"


// Constructor
AmbientLight::AmbientLight()
{
	ia_red = 50.0f;
	ia_green = 0.0f;
	ia_blue = 0.0f;
}

AmbientLight::AmbientLight(COLORREF colour)
{
	ia_red = GetRValue(colour);
	ia_green = GetGValue(colour);
	ia_blue = GetBValue(colour);
}

// Deconstructor
AmbientLight::~AmbientLight()
{
}

// GET
float AmbientLight::GetRedIntensity()
{
	return ia_red;
}
float AmbientLight::GetBlueIntensity()
{
	return ia_blue;
}
float AmbientLight::GetGreenIntensity()
{
	return ia_green;
}

// SET
void AmbientLight::SetRedIntensity(float red)
{
	ia_red = red;
}
void AmbientLight::SetBlueIntensity(float blue)
{
	ia_blue = blue;
}
void AmbientLight::SetGreenIntensity(float green)
{
	ia_green = green;
}
