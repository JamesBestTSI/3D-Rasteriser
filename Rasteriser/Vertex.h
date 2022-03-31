#pragma once

#include "Vector3D.h"
#include <windows.h>

class Vertex
{

public:
	// Constructors
	Vertex();
	Vertex(float x, float y);
	Vertex(float x, float y, float z);
	Vertex(float w, float x, float y, float z);

	// Copy constructor
	Vertex(const Vertex& v);

	// Destructer
	~Vertex();

	// Get
	float GetW() const;
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	Vector3D GetNormal() const;
	COLORREF GetColour() const;
	
	// Set
	void SetW(const float w);
	void SetX(const float x);
	void SetY(const float y);
	void SetZ(const float z);
	void SetNormal(const Vector3D norm);
	void SetColour(const COLORREF colour);

	// Operators
	const Vertex operator+  (const Vertex& rhs) const;		// VertexC = VertexA + VertexB
	Vertex&		 operator=  (const Vertex& rhs);			// VertexA = VertexB
	bool		 operator== (const Vertex& rhs) const;		// boolA = (VertexA == VertexB)
	bool		 operator!= (const Vertex& rhs) const;		// boolA = (VertexA != VertexB)

	Vector3D operator-  (Vertex& rhs);	// Vector3D = VertexA - VertexB

	// Modifiers
	void dehomogenize();

	int _contributingCount = 0;

private:
	// Values
	float _x;
	float _y;
	float _z;
	float _w;

	Vector3D _normal;
	COLORREF _colour;

};

