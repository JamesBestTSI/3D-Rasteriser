#include "Model.h"

// Constructor
Model::Model()
{
}

// Deconstructor
Model::~Model()
{
}

// GET
vector<Polygon3D>& Model::GetPolygons()
{
	return _polygons;
}
vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}
vector<Vertex>& Model::GetTransformedVertices()
{
	return _verticesTransformed;
}
size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}
size_t Model::GetVertexCount() const
{
	return _vertices.size();
}

//SET
void Model::AddVertex(float x, float y, float z)
{
	Vertex newVt(1, x, y, z);
	_vertices.push_back(newVt);
}
void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D newPg(i0, i1, i2);
	_polygons.push_back(newPg);
}

//Modifiers
void Model::ApplyTransformToLocalVertices(const Matrix & transform)
{
	_verticesTransformed.clear();
	for each (Vertex point in _vertices)
	{
		_verticesTransformed.push_back(transform*point);
	}
}

void Model::ApplyTransformToTransformedVertices(const Matrix & transform)
{
	for (Vertex &point : _verticesTransformed)
	{
		point = transform*point;
	}
}

void Model::DehomogenizeTransformedVertices()
{
	for (Vertex &point : _verticesTransformed)
	{
		point.dehomogenize();
	}
}

void Model::CalculateBackfaces(Vertex cameraPos)
{
	for (Polygon3D &poly : _polygons)
	{
		// Get the 3 indices of the vertices that make up the polygon    
		// Get the vertices for those indices
		Vertex vert0 = _verticesTransformed[poly.GetIndex(0)];
		Vertex vert1 = _verticesTransformed[poly.GetIndex(1)];
		Vertex vert2 = _verticesTransformed[poly.GetIndex(2)];

		// Construct vector a by subtracting vertex 1 from vertex 0.     
		Vector3D A = vert0 - vert1;
		// Construct vector b by subtracting vertex 2 from vertex 0.
		Vector3D B = vert0 - vert2;

		// Calculate the normal from vector b and a 
		poly.SetNormal(Vector3D::CrossProductOf(A, B));
		Vector3D normNormal = poly.GetNormal().Normalise();

		// Create eye-vector = vertex 0 - camera position 
		Vector3D eyeVector = vert0 - cameraPos;
		Vector3D normEye = eyeVector.Normalise();

		// Take dot product of the normal and eye-vector
		float DotProduct = Vector3D::DotProductOf(normNormal, normEye);
		//float DotProduct = Vector3D::DotProductOf(normal, eyeVector);
		
		// If result < 0        
		// Mark the polygon for culling
		if (DotProduct > 0)
		{
			poly.SetCulling(true);
		}
		else
		{
			poly.SetCulling(false);
		}
	}
	
}

void Model::CalculateVectorNormals()
{
	for (Vertex &vert : _verticesTransformed)
	{
		vert.SetNormal(Vector3D(0, 0, 0));
		vert._contributingCount = 0;
	}

	for (Polygon3D &poly : _polygons)
	{
		Vertex vert0 = _verticesTransformed[poly.GetIndex(0)];
		Vertex vert1 = _verticesTransformed[poly.GetIndex(1)];
		Vertex vert2 = _verticesTransformed[poly.GetIndex(2)];

		vert0.SetNormal(vert0.GetNormal() + poly.GetNormal());
		vert1.SetNormal(vert1.GetNormal() + poly.GetNormal());
		vert2.SetNormal(vert2.GetNormal() + poly.GetNormal());

		vert0._contributingCount++;
		vert1._contributingCount++;
		vert2._contributingCount++;
	}

	for (Vertex &vert : _verticesTransformed)
	{
		Vector3D norm(vert.GetNormal());
		Vector3D temp(Vector3D((norm.GetX() / vert._contributingCount), (norm.GetY() / vert._contributingCount), (norm.GetZ() / vert._contributingCount)));
		temp.Normalise();
		vert.SetNormal(temp);
	}
}

void Model::Sort()
{
	/*
	For each polygon in the model  
	Get each of the vertex indices for each polygon  
	Look up the transformed vertices for the polygon  
	Calculate an average z depth for the polygon vertices 
	Store this value back in the Polygon	
	Sort the polygon collection array to put furthest away first
	*/
	for (Polygon3D &poly : _polygons)
	{
		Vertex vert0 = _verticesTransformed[poly.GetIndex(0)];
		Vertex vert1 = _verticesTransformed[poly.GetIndex(1)];
		Vertex vert2 = _verticesTransformed[poly.GetIndex(2)];
		poly.SetAvgZDepth((vert0.GetZ() + vert1.GetZ() + vert2.GetZ()) / 3);
	}

	sort(_polygons.begin(), _polygons.end(), [](const Polygon3D& lhs, const Polygon3D& rhs) { return lhs.GetAvgZDepth() > rhs.GetAvgZDepth(); } );

	int stop = 0;
}



void Model::CalculateLightingDirectional(vector<DirectionalLight> directionalLights)
{
	int totalRed = 0;// GetRValue(poly.GetColour());
	int totalGreen = 0;// GetGValue(poly.GetColour());
	int totalBlue = 0;// GetBValue(poly.GetColour());
	int tempRed = 0;
	int tempGreen = 0;
	int tempBlue = 0;

	for (Polygon3D &poly : _polygons)
	{
		totalRed = GetRValue(poly.GetColour());
		totalGreen = GetGValue(poly.GetColour());
		totalBlue = GetBValue(poly.GetColour());

		for (DirectionalLight &light : directionalLights)
		{
			float DotProduct = Vector3D::DotProductOf(poly.GetNormal().Normalise(), light.GetDirection());

			tempRed = (int)((light.GetRedIntensity()*poly.GetRedReflect())*DotProduct);
			tempBlue = (int)((light.GetBlueIntensity()*poly.GetBlueReflect())*DotProduct);
			tempGreen = (int)((light.GetGreenIntensity()*poly.GetGreenReflect())*DotProduct);

			totalRed += tempRed;
			totalGreen += tempGreen;
			totalBlue += tempBlue;
		}

		if (totalRed > 255)
		{
			totalRed = 255;
		}
		if (totalGreen > 255)
		{
			totalGreen = 255;
		}
		if (totalBlue > 255)
		{
			totalBlue = 255;
		}

		if (totalRed < 0)
		{
			totalRed = 0;
		}
		if (totalGreen < 0)
		{
			totalGreen = 0;
		}
		if (totalBlue < 0)
		{
			totalBlue = 0;
		}

		poly.SetColour(RGB(totalRed, totalGreen, totalBlue));
	}
}


void Model::CalculateLightingAmbient(vector<AmbientLight> ambientLights)
{
	int totalRed = 0;// GetRValue(poly.GetColour());
	int totalGreen = 0;// GetGValue(poly.GetColour());
	int totalBlue = 0;// GetBValue(poly.GetColour());
	int tempRed = 0;
	int tempGreen = 0;
	int tempBlue = 0;
	for (Polygon3D &poly : _polygons)
	{
		totalRed = 0;
		totalGreen = 0;
		totalBlue = 0;

		for (AmbientLight &light : ambientLights)
		{
			tempRed = (int)(light.GetRedIntensity()*poly.GetRedReflect());
			tempBlue = (int)(light.GetBlueIntensity()*poly.GetBlueReflect());
			tempGreen = (int)(light.GetGreenIntensity()*poly.GetGreenReflect());

			totalRed += tempRed;
			totalGreen += tempGreen;
			totalBlue += tempBlue;
		}
		
		if (totalRed > 255)
		{
			totalRed = 255;
		}
		if (totalGreen > 255)
		{
			totalGreen = 255;
		}
		if (totalBlue > 255)
		{
			totalBlue = 255;
		}

		if (totalRed < 0)
		{
			totalRed = 0;
		}
		if (totalGreen < 0)
		{
			totalGreen = 0;
		}
		if (totalBlue < 0)
		{
			totalBlue = 0;
		}

		poly.SetColour(RGB(totalRed, totalGreen, totalBlue));
	}
}


void Model::CalculateLightingPoint(vector<PointLight> pointLights)
{
	int totalRed = 0;// GetRValue(poly.GetColour());
	int totalGreen = 0;// GetGValue(poly.GetColour());
	int totalBlue = 0;// GetBValue(poly.GetColour());
	int tempRed = 0;
	int tempGreen = 0;
	int tempBlue = 0;

	for (Polygon3D &poly : _polygons)
	{
		totalRed = GetRValue(poly.GetColour());
		totalGreen = GetGValue(poly.GetColour());
		totalBlue = GetBValue(poly.GetColour());

		for (PointLight &light : pointLights)
		{
			Vector3D lightVector = _verticesTransformed[poly.GetIndex(0)] - light.GetPos();
			float distance = lightVector.GetX() + lightVector.GetY() + lightVector.GetZ();
			//if (distance < 0)
			//{
			//	distance = distance - (distance * 2);
			//}

			//lightVector = lightVector.Normalise();

			float attenuation = 1 / (light.GetCoefficientA() + (light.GetCoefficientB()*distance) + (light.GetCoefficientC()*(distance*distance)));


			float DotProduct = Vector3D::DotProductOf(poly.GetNormal().Normalise(), lightVector);

			tempRed = (int)((light.GetRedIntensity()*poly.GetRedReflect())*DotProduct*attenuation);
			tempBlue = (int)((light.GetBlueIntensity()*poly.GetBlueReflect())*DotProduct*attenuation);
			tempGreen = (int)((light.GetGreenIntensity()*poly.GetGreenReflect())*DotProduct*attenuation);

			totalRed += tempRed;
			totalGreen += tempGreen;
			totalBlue += tempBlue;
		}

		if (totalRed > 255)
		{
			totalRed = 255;
		}
		if (totalGreen > 255)
		{
			totalGreen = 255;
		}
		if (totalBlue > 255)
		{
			totalBlue = 255;
		}

		if (totalRed < 0)
		{
			totalRed = 0;
		}
		if (totalGreen < 0)
		{
			totalGreen = 0;
		}
		if (totalBlue < 0)
		{
			totalBlue = 0;
		}

		poly.SetColour(RGB(totalRed, totalGreen, totalBlue));
	}
}



void Model::SetPolyColour()
{
	for (Polygon3D &poly : _polygons)
	{
		poly.SetColour(RGB(0, 0, 0));
	}
}