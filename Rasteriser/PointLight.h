#pragma once
#include <windows.h>
#include "Vertex.h"
#include "Vector3D.h"

class PointLight
{

public:

	// Constructor
	PointLight();
	PointLight(Vertex pos);
	PointLight(Vertex pos, COLORREF colour);

	// Deconstructor
	~PointLight();

	// Get
	Vertex GetPos();
	float GetRedIntensity();
	float GetBlueIntensity();
	float GetGreenIntensity();

	float GetCoefficientA();
	float GetCoefficientB();
	float GetCoefficientC();

	// Set
	void SetPos(Vertex pos);
	void SetRedIntensity(float red);
	void SetBlueIntensity(float blue);
	void SetGreenIntensity(float green);

private:

	float ip_red, ip_green, ip_blue;
	float coefficient_a, coefficient_b, coefficient_c;
	Vertex _Position;
};

