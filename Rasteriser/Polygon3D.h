#pragma once
#include <windows.h>
#include "Vector3D.h"

class Polygon3D
{

public:

	// Default constructor
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);

	// Copy constructor. 
	Polygon3D(const Polygon3D& p);

	// Destructer
	~Polygon3D();

	// Get
	int GetIndex(int pos) const;

	Vector3D GetNormal() const;
	float GetAvgZDepth() const;
	bool GetCulling() const;

	COLORREF GetColour() const;
	float GetRedReflect() const;
	float GetGreenReflect() const;
	float GetBlueReflect() const;

	//SET
	void SetNormal(Vector3D polyNormal);
	void SetAvgZDepth(float zDepth);
	void SetCulling(bool cull);

	void SetColour(COLORREF colour);
	void SetRedReflect(float red);
	void SetGreenReflect(float green);
	void SetBlueReflect(float blue);

	// Operators
	Polygon3D& operator= (const Polygon3D &rhs);

private:
	int _indices[3];

	Vector3D _polyNormal;
	float _polysAvgZDepth;
	bool _culling;

	COLORREF _polygonColour;
	float kd_red, kd_green, kd_blue;

};

