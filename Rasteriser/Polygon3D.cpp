#include "Polygon3D.h"


// Constructors
Polygon3D::Polygon3D()
{
	_indices[0] = 0;
	_indices[1] = 0;
	_indices[2] = 0;

	_polysAvgZDepth = 0;
	_culling		= false;

	SetColour(RGB(0, 0, 0));
	kd_red = 0.80f;
	kd_green = 0.80f;
	kd_blue = 0.80f;
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;

	_polysAvgZDepth = 0;
	_culling		= false;

	SetColour(RGB(0,0,0));
	kd_red = 0.80f;
	kd_green = 0.80f;
	kd_blue = 0.80f;
}

Polygon3D::Polygon3D(const Polygon3D & p)
{
	_indices[0] = p.GetIndex(0);
	_indices[1] = p.GetIndex(1);
	_indices[2] = p.GetIndex(2);

	_polysAvgZDepth = p.GetAvgZDepth();
	_culling		= p.GetCulling();

	_polygonColour	= p.GetColour();
	kd_red			= p.GetRedReflect();
	kd_green		= p.GetGreenReflect(); 
	kd_blue			= p.GetBlueReflect();
}

// Deconstructor
Polygon3D::~Polygon3D()
{
}


// Get
int Polygon3D::GetIndex(int pos) const
{
	return _indices[pos];
}
Vector3D Polygon3D::GetNormal() const
{
	return _polyNormal;
}
float Polygon3D::GetAvgZDepth() const
{
	return _polysAvgZDepth;
}
bool Polygon3D::GetCulling() const
{
	return _culling;
}
COLORREF Polygon3D::GetColour() const
{
	return _polygonColour;
}
float Polygon3D::GetRedReflect() const
{
	return kd_red;
}
float Polygon3D::GetGreenReflect() const
{
	return kd_green;
}
float Polygon3D::GetBlueReflect() const
{
	return kd_blue;
}


// Set
void Polygon3D::SetNormal(Vector3D polyNormal)
{
	_polyNormal = polyNormal;
}
void Polygon3D::SetAvgZDepth(float zDepth)
{
	_polysAvgZDepth = zDepth;
}
void Polygon3D::SetCulling(bool cull)
{
	_culling = cull;
}
void Polygon3D::SetColour(COLORREF colour)
{
	_polygonColour = colour;
}
void Polygon3D::SetRedReflect(float red)
{
	kd_red = red;
}
void Polygon3D::SetGreenReflect(float green)
{
	kd_green = green;
}
void Polygon3D::SetBlueReflect(float blue)
{
	kd_blue = blue;
}


// Operators
Polygon3D& Polygon3D::operator=(const Polygon3D & rhs)
{
	_indices[0] = rhs.GetIndex(0);
	_indices[1] = rhs.GetIndex(1);
	_indices[2] = rhs.GetIndex(2);

	_polysAvgZDepth = rhs.GetAvgZDepth();
	_culling		= rhs.GetCulling();

	_polygonColour  = rhs.GetColour();
	kd_red			= rhs.GetRedReflect();
	kd_green		= rhs.GetGreenReflect();
	kd_blue			= rhs.GetBlueReflect();

	return *this;
}
