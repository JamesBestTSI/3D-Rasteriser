#pragma once

#include <math.h>       /* sqrt */
class Vector3D
{
public:

	// Constructors
	Vector3D();
	Vector3D(float x, float y, float z);

	// Copy constructor.  
	Vector3D(const Vector3D& v);

	// Destructer
	~Vector3D();

	// Get
	float GetX() const;
	float GetY() const;
	float GetZ() const;

	// Set
	void SetX(const float x);
	void SetY(const float y);
	void SetZ(const float z);


	static Vector3D CrossProductOf(Vector3D A, Vector3D B);
	static float DotProductOf(Vector3D A, Vector3D B);

	const Vector3D operator+  (const Vector3D& rhs) const;


	// Modifiers
	Vector3D Normalise();

private:
	float _x;
	float _y;
	float _z;
};

