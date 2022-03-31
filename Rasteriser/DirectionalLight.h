#pragma once
#include <windows.h>
#include "Vector3D.h"

class DirectionalLight
{

public:

	// Constructor
	DirectionalLight();
	DirectionalLight(Vector3D direction);
	DirectionalLight(Vector3D direction, COLORREF colour);

	// Deconstructor
	~DirectionalLight();

	// Get
	Vector3D GetDirection();
	float GetRedIntensity();
	float GetBlueIntensity();
	float GetGreenIntensity();

	// Set
	void SetDirection(Vector3D direction);
	void SetRedIntensity(float red);
	void SetBlueIntensity(float blue);
	void SetGreenIntensity(float green);

private:

	float id_red, id_green, id_blue;
	Vector3D Direction;
};

