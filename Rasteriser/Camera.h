#pragma once
#include "Vertex.h"
#include "Matrix.h"

class Camera
{

public:

	// Constructors
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);

	//Deconstructor
	~Camera();

	// Get
	float GetXRotation();
	float GetYRotation();
	float GetZRotation();
	Vertex GetPos();
	Matrix GetMatrix();

	// Set
	void SetXRotation(float x);
	void SetYRotation(float y);
	void SetZRotation(float z);
	void SetPos(Vertex pos);
	void SetAll(float xRotation, float yRotation, float zRotation, const Vertex& position);


	// Get xRotation
	float XRotation()			{ return xRotation; }
	// Set xRotation
	void  XRotation(float x)	{ xRotation = x; MakeMatrix();}
	// Get yRotation
	float YRotation()			{ return yRotation; }
	// Set yRotation
	void  YRotation(float y)	{ yRotation = y; MakeMatrix();}
	// Get zRotation
	float ZRotation()			{ return zRotation; }
	// Set zRotation
	void  ZRotation(float z)	{ zRotation = z; MakeMatrix();}
	// Get position
	Vertex Pos()				{ return position; }
	// Set position
	void Pos(Vertex pos)		{ position = pos; }

	// Make cameraMatrix
	void MakeMatrix();

private:
	float xRotation;
	float yRotation;
	float zRotation;
	Vertex position;
	Matrix cameraMatrix;

};

