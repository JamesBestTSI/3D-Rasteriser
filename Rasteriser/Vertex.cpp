#include "Vertex.h"

// Constructors
Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 0.0f;
}

Vertex::Vertex(float x, float y)
{
	_w = 0.0f;
	_x = x;
	_y = y;
	_z = 0.0f;
}

Vertex::Vertex(float x, float y, float z)
{
	_w = 1.0f;
	_x = x;
	_y = y;
	_z = z;
}

Vertex::Vertex(float w, float x, float y, float z)
{
	_w = w;
	_x = x;
	_y = y;
	_z = z;
}

// Copy constructor implementation
Vertex::Vertex(const Vertex& v)
{
	_w = v.GetW();
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_normal = v.GetNormal();
	_colour = v.GetColour();
}

// Destructor does not need to do anything
Vertex::~Vertex()
{
}


// GET
float Vertex::GetW() const
{
	return _w;
}
float Vertex::GetX() const
{
	return _x;
}
float Vertex::GetY() const
{
	return _y;
}
float Vertex::GetZ() const
{
	return _z;
}

Vector3D Vertex::GetNormal() const
{
	return _normal;
}

COLORREF Vertex::GetColour() const
{
	return _colour;
}

// SET
void Vertex::SetW(const float w)
{
	_w = w;
}
void Vertex::SetX(const float x)
{
	_x = x;
}
void Vertex::SetY(const float y)
{
	_y = y;
}
void Vertex::SetZ(const float z)
{
	_z = z;
}

void Vertex::SetNormal(const Vector3D norm)
{
	_normal = norm;
}

void Vertex::SetColour(const COLORREF colour)
{
	_colour = colour;
}

/// Operators
// Vertex A + Vertex B
const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_w + rhs.GetW(), _x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}

// Vertex A = Vertex B
Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning to ourselves
	if (this != &rhs)
	{
		_w = rhs.GetW();
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_normal = rhs.GetNormal();
		_colour = rhs.GetColour();
	}
	return *this;
}

// if (Vertex A == Vertex B)
bool Vertex::operator==(const Vertex& rhs) const
{
	return (_w == rhs.GetW() && _x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ());
}

// if (Vertex A != Vertex B)
bool Vertex::operator!=(const Vertex& rhs) const
{
	return (_w != rhs.GetW() || _x != rhs.GetX() || _y != rhs.GetY() || _z != rhs.GetZ());
}

// Vertex A - Vertex B
Vector3D Vertex::operator-(Vertex & rhs)
{
	Vertex temp = Vertex(_w - rhs.GetW(), _x - rhs.GetX(), _y - rhs.GetY(), _z - rhs.GetZ());
	Vector3D output(temp.GetX(), temp.GetY(), temp.GetZ());
	return output;
}

/// Modifiers
// Transform from 4D to 3D
void Vertex::dehomogenize()
{
	_x = _x / _w;
	_y = _y / _w;
	_z = _z / _w;
	_w = 1.0f;
}