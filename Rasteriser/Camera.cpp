#include "Camera.h"
#include "Matrix.h"

// Constructors
Camera::Camera()
{
	xRotation = 0;
	yRotation = 0;
	zRotation = 0;
	position = Vertex(0,0,0,1);
	MakeMatrix();
}
Camera::Camera(float xRot, float yRot, float zRot, const Vertex& pos)
{
	xRotation = xRot;
	yRotation = yRot;
	zRotation = zRot;
	position = pos;
	MakeMatrix();
}

// Deconstructor
Camera::~Camera()
{
}

// Get
float Camera::GetXRotation()
{
	return xRotation;
}
float Camera::GetYRotation()
{
	return yRotation;
}
float Camera::GetZRotation()
{
	return zRotation;
}
Vertex Camera::GetPos()
{
	return position;
}
Matrix Camera::GetMatrix()
{
	return cameraMatrix;
}

// Set (Note: whenever we change a value we will need to update the cameraMatrix)
void Camera::SetXRotation(float x)
{
	xRotation = x;
	MakeMatrix();
}
void Camera::SetYRotation(float y)
{
	yRotation = y;
	MakeMatrix();
}
void Camera::SetZRotation(float z)
{
	zRotation = z;
	MakeMatrix();
}
void Camera::SetPos(Vertex pos)
{
	position = pos;
	MakeMatrix();
}

void Camera::SetAll(float x, float y, float z, const Vertex & pos)
{
	xRotation = x;
	yRotation = y;
	zRotation = z;
	position = pos;
	MakeMatrix();
}

// Make cameraMatrix
void Camera::MakeMatrix()
{
	cameraMatrix = Matrix::RotationMatrix(xRotation, yRotation, zRotation)*Matrix::TransformMatrix(-position.GetX(), -position.GetY(), -position.GetZ());
}