#pragma once
#include <windows.h>

class AmbientLight
{
public:

	// Constructor
	AmbientLight();
	AmbientLight(COLORREF colour);
	
	// Deconstructor
	~AmbientLight();

	// Get
	float GetRedIntensity();
	float GetBlueIntensity();
	float GetGreenIntensity();

	// Set
	void SetRedIntensity(float red);
	void SetBlueIntensity(float blue);
	void SetGreenIntensity(float green);

private:

	float ia_red, ia_green, ia_blue;
};

