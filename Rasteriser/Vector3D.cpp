#include "Vector3D.h"

// Constructors
Vector3D::Vector3D()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}
// Copy constructor. 
Vector3D::Vector3D(const Vector3D & v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
}

// Destructer
Vector3D::~Vector3D()
{
}

// Get
float Vector3D::GetX() const
{
	return _x;
}
float Vector3D::GetY() const
{
	return _y;
}
float Vector3D::GetZ() const
{
	return _z;
}

// Set
void Vector3D::SetX(const float x)
{
	_x = x;
}
void Vector3D::SetY(const float y)
{
	_y = y;
}
void Vector3D::SetZ(const float z)
{
	_z = z;
}


Vector3D Vector3D::CrossProductOf(Vector3D A, Vector3D B)
{
	Vector3D Cross;
	Cross.SetX((A.GetY()*B.GetZ()) - (A.GetZ()*B.GetY()));
	Cross.SetY((A.GetZ()*B.GetX()) - (A.GetX()*B.GetZ()));
	Cross.SetZ((A.GetX()*B.GetY()) - (A.GetY()*B.GetX()));
	return Cross;
}

float Vector3D::DotProductOf(Vector3D A, Vector3D B)
{
	float dot = (A.GetX()*B.GetX()) + (A.GetY()*B.GetY()) + (A.GetZ()*B.GetZ());
	return dot;
}

const Vector3D Vector3D::operator+(const Vector3D & rhs) const
{
	Vector3D temp;
	temp.SetX(GetX() + rhs.GetX());
	temp.SetY(GetY() + rhs.GetY());
	temp.SetZ(GetZ() + rhs.GetZ());
	return temp;
}

// Modifiers
Vector3D Vector3D::Normalise()
{
	float mag = (float)sqrt(this->GetX()*this->GetX()) + (this->GetY()*this->GetY()) + (this->GetZ()*this->GetZ());

	Vector3D norm(this->GetX() / mag, this->GetY() / mag, this->GetZ() / mag);
	return norm;
}