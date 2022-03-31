#pragma once
#include <vector>
#include "Polygon3D.h"
#include "Vertex.h"
#include "Matrix.h"
#include <algorithm> 
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"


using namespace std;

class Model
{

public:

	// Default constructor
	Model();

	// Destructer
	~Model();

	// GET
	vector <Polygon3D>& GetPolygons();
	vector <Vertex>& GetVertices();
	vector <Vertex>& GetTransformedVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;

	//SET
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	// Modifiers
	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);
	void DehomogenizeTransformedVertices();

	void CalculateBackfaces(Vertex cameraPos);
	void CalculateVectorNormals();
	void Sort();

	void CalculateLightingDirectional(vector <DirectionalLight> directionalLights);
	void CalculateLightingAmbient(vector <AmbientLight> ambientLights);
	void CalculateLightingPoint(vector <PointLight> pointLights);
	void SetPolyColour();

private:
	vector <Polygon3D> _polygons;
	vector <Vertex> _vertices;
	vector <Vertex> _verticesTransformed;
};

