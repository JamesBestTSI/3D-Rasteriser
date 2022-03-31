#pragma once
#include <vector>
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Polygon3D.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"

class Rasteriser : public Framework
{
public:
	bool Initialise();
	void Update(Bitmap &bitmap);
	void Render(Bitmap &bitmap);

	/// Drawing Lines
	void DrawLine(HDC hdc, float fromX, float fromY, float toX, float toY);
	void DrawLine(HDC hdc, float fromX, float fromY, Vertex &to);
	void DrawLine(HDC hdc, Vertex &from, float toX, float toY);
	void DrawLine(HDC hdc, Vertex &from, Vertex &to);
	void DrawLine(HDC hdc, COLORREF colour, Vertex &from, Vertex &to);
	
	/// Draw Model (Wireframe Or Flat)
	void DrawWireFrame(Bitmap &bitmap);
	void DrawSolidFlat(Bitmap &bitmap);
	void MyDrawSolidFlat(Bitmap &bitmap);
	void FillPolygonFlat(Bitmap & bitmap, vector <Vertex> verts, COLORREF colour);

	/// Transforming a Model
	void TransformModel(Model &modelToTransform);

	/// Create Matrix's
	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);

	/// Creating Lights (Fast way)
	void CreateAmbientLight(COLORREF colour);
	void CreateDirectionalLight(Vector3D direction, COLORREF colour);
	void CreatePointLight(Vertex pos, COLORREF colour);

	/// Timer based things
	Matrix TimedTransformMatrix();
	void SwitchTypeCheck();
	void LightTypeCheck(Model &modelToTransform);

	/// Onscreen Display
	void DisplayText(Bitmap &bitmap);



private:
	// Bools needed to check current states
	bool _initialised = false;
	bool wireframe = true;
	bool cull = false;
	bool lights = false;
	bool drawMyPolys = false;

	// Objects
	Camera mainCam;
	Model currentModel;

	// Light Values
	vector <DirectionalLight> DirectionalLights;
	vector <AmbientLight> AmbientLights;
	vector <PointLight> PointLights;

	// Matrix's used for the scale, transform and rotations
	Matrix perspectiveMatrix;
	Matrix viewMatrix;
	Matrix transformMatrix;

	// Values used to write on screen
	LPCWSTR _onScreenText = L"";
	LPCWSTR _onScreenRenderType = L"";
	LPCWSTR _onScreenCullType = L"";
	LPCWSTR _onScreenLightType = L"";
	LPCWSTR _onScreenPolyType = L"";

	// Timer used to switch between outputs
	int _timeCounter = 0;
};