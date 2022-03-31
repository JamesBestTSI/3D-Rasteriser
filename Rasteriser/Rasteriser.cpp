#include "Rasteriser.h"

Rasteriser app;

/**
	The Initialise function is run at the start to make sure that all of our 
	objects are loaded in and also set to their starting values.
*/
bool Rasteriser::Initialise()
{	
	// Set the location of the camera
	mainCam.SetAll(0, 0, 0, Vertex(0, 0, -50));

	// Create and Add a Light (New way)
	//	NOTE: The old way of creating a light was to create the instance of a light and then puch it back on to 
	//	the vector list of that light type. This way is much faster to call as a function and cleaner to look at.
	CreateAmbientLight(RGB(125, 60, 60));
	CreateDirectionalLight(Vector3D(5, 10, 0), RGB(0, 0, 255));
	CreatePointLight(Vertex(20, 20, -7), RGB(200, 200, 200));

	// Load the model md2 file into the currentModel instance
	if (!MD2Loader::LoadModel("astro.md2", currentModel, &Model::AddPolygon, &Model::AddVertex))
	{return false;}

	_initialised = true;
	return true;
}

/**
	The Update function is used to run all the functions needed in order to perform a full update per frame.

	Firstly we will check to make sure that the class has had everything initialised.
	Once everything has been initialised, we then proceed to perform the updates.
	* Generate a view Matrix for the window - (if window size changes this will update)
	* Generate a perspective Matrix for the window - (if window size changes this will update)
	* Update our transform matrix based on our timer - (Depending on where we are in the timer depends on the transform that gets applied)
	* Check our render types and our timer - (This is where it will change render types eg wireframe/solid/lights)
	* Apply the transforms to the model - (This includes the Camers, World, Perspective and colours based on lights)
	* Update our timer
	* Display the types of rendering done on screen

	@param bitmap The current bitmap that we wish to update.
*/
void Rasteriser::Update(Bitmap &bitmap)
{
	// Check to see if we have initialised everything first
	if (_initialised)
	{
		// Generate a view Matrix for the window
		GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());

		// Generate a perspective Matrix for the window
		GeneratePerspectiveMatrix((float)1, (float)bitmap.GetWidth() / bitmap.GetHeight());
		
		// Update our transform matrix based on our timer
		transformMatrix = TimedTransformMatrix();
		/*
			Other ways of changing the matrix
			transformMatrix = Matrix::RotationMatrix(0, 2.5 * _timeCounter, 0);
			transformMatrix = Matrix::ScaleMatrix((float)_timeCounter / 100, (float)_timeCounter / 100, (float)_timeCounter / 100);
		*/

		// Checks our render types and our timer and changes culling 
		// on or off and wireframe and lights on or off based on our timer
		SwitchTypeCheck();
		
		// Apply the transforms to the model
		TransformModel(currentModel);

		// Update our timer
		_timeCounter++;

		// Display the types of rendering done on screen
		DisplayText(bitmap);
	}
}

/**
	The Render function is what we use to actually draw to the screen the updates.

	Firstly we will want to clear the screen to a blank colour
	Then we will want to either draw the wireframe or draw the solid model.
	Making sure to update the text depending on what we choose.

	@param bitmap The current bitmap that we wish to update.
*/
void Rasteriser::Render(Bitmap &bitmap)
{
	//. Clear the bitmap to white
	bitmap.Clear(RGB(255, 255, 255));

	// Depending on the render type, we either draw the wireframe or a solid model.
	if (wireframe)
	{
		_onScreenRenderType = L"Wireframe";
		DrawWireFrame(bitmap);
	}
	else 
	{
		_onScreenRenderType = L"Solid Model";

		if (!drawMyPolys)
		{
			_onScreenPolyType = L"Windows Polygon Draw";
			DrawSolidFlat(bitmap);
		}
		else
		{
			_onScreenPolyType = L"My Polygon Draw";
			MyDrawSolidFlat(bitmap);
		}
	}
}




/******************************************/
/// DRAWING LINES (using Floats and Vertex's)
/******************************************/

/**
	The DrawLine function draws a line from one place on screen to another.

	@param hdc The current bitmaps HDC that we wish to draw to.
	@param fromX The starting X position.
	@param fromY The starting Y position.
	@param toX The end X position.
	@param toY The end Y position.
*/
void Rasteriser::DrawLine(HDC hdc, float fromX, float fromY, float toX, float toY)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(255, 0, 0));

	MoveToEx(hdc, (int)fromX, (int)fromY, NULL);
	LineTo(hdc, (int)toX, (int)toY);
}

/**
	The DrawLine function draws a line from one place on screen to another.

	@param hdc The current bitmaps HDC that we wish to draw to.
	@param from A Vertex that contains the starting X and Y position.
	@param toX The end X position.
	@param toY The end Y position.
*/
void Rasteriser::DrawLine(HDC hdc, Vertex &from, float toX, float toY)
{
	DrawLine(hdc, from.GetX(), from.GetY(), toX, toY);
}

/**
	The DrawLine function draws a line from one place on screen to another.

	@param hdc The current bitmaps HDC that we wish to draw to.
	@param fromX The starting X position.
	@param fromY The starting Y position.
	@param to A Vertex that contains the end X and Y position.
*/
void Rasteriser::DrawLine(HDC hdc, float fromX, float fromY, Vertex &to)
{
	DrawLine(hdc, fromX, fromY, to.GetX(), to.GetY());
}

/**
	The DrawLine function draws a line from one place on screen to another.

	@param hdc The current bitmaps HDC that we wish to draw to.
	@param from A Vertex that contains the starting X and Y position.
	@param to A Vertex that contains the end X and Y position.
*/
void Rasteriser::DrawLine(HDC hdc, Vertex &from, Vertex &to)
{
	DrawLine(hdc, from.GetX(), from.GetY(), to.GetX(), to.GetY());
}

/**
	The DrawLine function draws a line from one place on screen to another.

	@param hdc The current bitmaps HDC that we wish to draw to.
	@pram colour The colour of the Line we wish to draw.
	@param from A Vertex that contains the starting X and Y position.
	@param to A Vertex that contains the end X and Y position.
*/
void Rasteriser::DrawLine(HDC hdc, COLORREF colour, Vertex &from, Vertex &to)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, colour);

	MoveToEx(hdc, (int)from.GetX(), (int)from.GetY(), NULL);
	LineTo(hdc, (int)to.GetX(), (int)to.GetY());
}




/******************************************/
/// DRAWING THE MODEL (Wireframe/Solid)
/******************************************/

/**
	The DrawWireFrame function is used to draw a wireframe of our Model.

	We loop through all the currentModel Polygons and if the polygon is not set to be culled
	then we get all three Vertex's and draw the lines needed to create the polygon.
	Because we loop through all the polygons in the model, this effectivly draws the model wireframe.

	@param bitmap The current bitmap that we wish to draw to.
*/
void Rasteriser::DrawWireFrame(Bitmap & bitmap)
{
	vector <Vertex> _verts = currentModel.GetTransformedVertices();
	for each (Polygon3D polygon in currentModel.GetPolygons())
	{
		if (!polygon.GetCulling())
		{
			DrawLine(bitmap.GetDC(), _verts[polygon.GetIndex(0)], _verts[polygon.GetIndex(1)]);
			DrawLine(bitmap.GetDC(), _verts[polygon.GetIndex(1)], _verts[polygon.GetIndex(2)]);
			DrawLine(bitmap.GetDC(), _verts[polygon.GetIndex(2)], _verts[polygon.GetIndex(0)]);
		}
	}
}

/**
	The DrawSolidFlat function is used to draw a solid image of our Model.

	We loop through all the currentModel Polygons and if the polygon is not set to be culled
	then we get all three Vertex's that make up the polygon and convert them to 'POINT' types
	When we have the list of POINT's we can then draw the polygon using the Polygon function.
	Because we loop through all the polygons in the model, this effectivly draws the solid image of the model.

	@param bitmap The current bitmap that we wish to draw to.
*/
void Rasteriser::DrawSolidFlat(Bitmap & bitmap)
{
	vector <Vertex> _verts = currentModel.GetTransformedVertices();
	for each (Polygon3D polygon in currentModel.GetPolygons())
	{
		if (!polygon.GetCulling())
		{
			POINT points[3];

			// Get the x and y for each of the transformed vertex points of the polygon and store them as a POINT
			for (int counter = 0; counter < 3; counter++)
			{
				points[counter].x = (LONG)_verts[polygon.GetIndex(counter)].GetX();
				points[counter].y = (LONG)_verts[polygon.GetIndex(counter)].GetY();
			}

			SelectObject(bitmap.GetDC(), GetStockObject(DC_PEN));
			SetDCPenColor(bitmap.GetDC(), polygon.GetColour());

			SelectObject(bitmap.GetDC(), GetStockObject(DC_BRUSH));
			SetDCBrushColor(bitmap.GetDC(), polygon.GetColour());

			Polygon(bitmap.GetDC(), points, 3);
		}
	}
}

/**
	The MyDrawSolidFlat function is used to draw a solid image of our Model.

	We loop through all the currentModel Polygons and if the polygon is not set to be culled
	then we get all three Vertex's that make up the polygon and add them to a vector list of Vertex's
	These are then passed over to the custom draw polygon function.
	Because we loop through all the polygons in the model, this effectivly draws the solid image of the model.

	@param bitmap The current bitmap that we wish to draw to.
*/
void Rasteriser::MyDrawSolidFlat(Bitmap & bitmap)
{
	vector <Vertex> _verts = currentModel.GetTransformedVertices();
	for each (Polygon3D polygon in currentModel.GetPolygons())
	{
		if (!polygon.GetCulling())
		{
			vector<Vertex> verts;
			verts.push_back(_verts[polygon.GetIndex(0)]);
			verts.push_back(_verts[polygon.GetIndex(1)]);
			verts.push_back(_verts[polygon.GetIndex(2)]);

			FillPolygonFlat(bitmap, verts, polygon.GetColour());
		}
	}
}

/**
	The FillPolygonFlat function is used to draw a polygon.

	We get the max and mix x and y vales to find the bounding box.
	Then create 2 Vectors from the vertex's that make up the polygon.
	We then loop through all the pixels inside of our bounding box and work out if it is inside of out polygon or not.
	If it is inside of out polygon then we set the pixel at x,y to the colour of the polygon

	@param bitmap The current bitmap that we wish to draw to.
	@param verts The current vertex's that make up the polygon.
	@param colour The current polygon's colour.
*/
void Rasteriser::FillPolygonFlat(Bitmap & bitmap, vector<Vertex> verts, COLORREF colour)
{
	/* get the bounding box of the triangle */

	float maxX = max(verts[0].GetX(), verts[1].GetX());
	maxX = max(maxX, verts[2].GetX());
	float maxY = max(verts[0].GetY(), verts[1].GetY());
	maxY = max(maxY, verts[2].GetY());
	float minX = min(verts[0].GetX(), verts[1].GetX());
	minX = min(minX, verts[2].GetX());
	float minY = min(verts[0].GetY(), verts[1].GetY());
	minY = min(minY, verts[2].GetY());

	Vector3D v1 = verts[1] - verts[0];
	Vector3D v2 = verts[2] - verts[0];
	
	for (float x = minX; x <= maxX; x++)
	{
		for (float y = minY; y <= maxY; y++)
		{
			Vector3D q(x - verts[0].GetX(), y - verts[0].GetY(), (float)0);

			float s = ((q.GetX()*v2.GetY()) - (q.GetY()*v2.GetX())) / ((v1.GetX()*v2.GetY()) - (v1.GetY()*v2.GetX()));
			float t = ((v1.GetX()*q.GetY()) - (v1.GetY()*q.GetX())) / ((v1.GetX()*v2.GetY()) - (v1.GetY()*v2.GetX()));

			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				SetPixel(bitmap.GetDC(), (int)x, (int)y, colour);
			}
		}
	}
}





/******************************************/
/// TRANSFORMING A MODEL
/******************************************/

/**
TransformModel applies the different transforms to the model in order for it to be correctly rendered on screen.

I was tempted to create a copy of this function and have it so that you could pass through not only
the model but also the transform matrix, this would allow us to pass through another model with a
different transform matrix and thus display another model at a different location doing a different
transformation eg rotation the other way to the first model.
*/
void Rasteriser::TransformModel(Model &modelToTransform)
{
	// World Transform
	modelToTransform.ApplyTransformToLocalVertices(transformMatrix);


	// BackFace Culling
	if (cull)
	{
		_onScreenCullType = L"Culling";
		modelToTransform.CalculateBackfaces(mainCam.GetPos());
	}
	else
	{
		_onScreenCullType = L"No Culling";
	}


	// NOT COMPLETE (Generating Normal Vectors for Each Vertex)
	//modelToTransform.CalculateVectorNormals();

	// Calculate Polygon Colour
	LightTypeCheck(modelToTransform);


	// Camera Transform
	modelToTransform.ApplyTransformToTransformedVertices(mainCam.GetMatrix());


	// Sort the polygons
	modelToTransform.Sort();


	// Perspective Transform
	modelToTransform.ApplyTransformToTransformedVertices(perspectiveMatrix);


	// Dehomogenize Vertex's
	modelToTransform.DehomogenizeTransformedVertices();


	// View Transform
	modelToTransform.ApplyTransformToTransformedVertices(viewMatrix);
}





/******************************************/
/// CREATE MATRIX'S (Prespective/View)
/******************************************/

/**
	The GeneratePerspectiveMatrix function is used to create a perspective matrix.
	
	@param d The field of view or the focal length of the camera
	@param aspectRatio The Width divided by Height
*/
void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	perspectiveMatrix.SetM(0, 0, d / aspectRatio);
	perspectiveMatrix.SetM(1, 1, d);
	perspectiveMatrix.SetM(2, 2, d);
	perspectiveMatrix.SetM(3, 2, 1);
}

/**
	The GenerateViewMatrix function is used to create a view matrix.

	@param d The field of view or the focal length of the camera
	@param width The Width of the window/bitmap viewed
	@param height The Height of the window/bitmap viewed
*/
void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	viewMatrix.SetM(0, 0, (float)width / 2);
	viewMatrix.SetM(0, 3, (float)width / 2);
	viewMatrix.SetM(1, 1, (float)-height / 2);
	viewMatrix.SetM(1, 3, (float)height / 2);
	viewMatrix.SetM(2, 3, (float)d / 2);
	viewMatrix.SetM(2, 2, (float)d / 2);
	viewMatrix.SetM(3, 3, (float)1);
}





/******************************************/
/// CREATING LIGHTS (Fast way)
/******************************************/

/**
	CreateAmbientLight takes the same arguments you would use to create a instance of a Light
	However it also adds the light to the list of current Ambient lights.
*/
void Rasteriser::CreateAmbientLight(COLORREF colour)
{
	AmbientLight ALight(colour);
	AmbientLights.push_back(ALight);
}

/**
	CreateDirectionalLight takes the same arguments you would use to create a instance of a Light
	However it also adds the light to the list of current Directional lights.
*/
void Rasteriser::CreateDirectionalLight(Vector3D direction, COLORREF colour)
{
	DirectionalLight DLight(direction, colour);
	DirectionalLights.push_back(DLight);
}

/**
	CreatePointLight takes the same arguments you would use to create a instance of a Light
	However it also adds the light to the list of current Point lights.
*/
void Rasteriser::CreatePointLight(Vertex pos, COLORREF colour)
{
	PointLight PLight(pos, colour);
	PointLights.push_back(PLight);
}

// Changes the lights rendered based on the timer
void Rasteriser::LightTypeCheck(Model &modelToTransform)
{
	if (lights)
	{
		if (_timeCounter > 599 && _timeCounter < 700)
		{
			modelToTransform.SetPolyColour();
			modelToTransform.CalculateLightingAmbient(AmbientLights);
			_onScreenLightType = L"Ambient Light";
		}
		if (_timeCounter > 699 && _timeCounter < 800)
		{
			modelToTransform.SetPolyColour();
			modelToTransform.CalculateLightingDirectional(DirectionalLights);
			_onScreenLightType = L"Directional Light";
		}
		if (_timeCounter > 799 && _timeCounter < 900)
		{
			modelToTransform.SetPolyColour();
			modelToTransform.CalculateLightingPoint(PointLights);
			_onScreenLightType = L"Point Light";
		}


		if (_timeCounter > 899 && _timeCounter < 1000)
		{
			modelToTransform.SetPolyColour();
			modelToTransform.CalculateLightingAmbient(AmbientLights);
			modelToTransform.CalculateLightingDirectional(DirectionalLights);
			_onScreenLightType = L"Ambient + Directional Light";
		}
		if (_timeCounter > 999)
		{
			modelToTransform.SetPolyColour();
			modelToTransform.CalculateLightingAmbient(AmbientLights);
			modelToTransform.CalculateLightingDirectional(DirectionalLights);
			modelToTransform.CalculateLightingPoint(PointLights);
			_onScreenLightType = L"Ambient + Directional + Point Light";
		}
		if (_timeCounter > 1200)
		{
			drawMyPolys = true;
		}
	}
}





/******************************************/
/// EXTRA TIMER BASED STUFF
/******************************************/

/**
TimedTransformMatrix returns a transform matrix based on the current timer value.

This is only really used to show off all of the differnet types of matrix transformations working.
*/
Matrix Rasteriser::TimedTransformMatrix()
{
	if (_timeCounter < 66)
	{
		_onScreenText = L"Move X";
		return Matrix::TransformMatrix((float)_timeCounter / 10, 0, 0);
	}

	else if (_timeCounter >65 && _timeCounter < 132)
	{
		_onScreenText = L"Move Y";
		return Matrix::TransformMatrix(0, (float)_timeCounter / 10, 0);
	}

	else if (_timeCounter >131 && _timeCounter < 200)
	{
		_onScreenText = L"Move Z";
		return Matrix::TransformMatrix(0, 0, (float)_timeCounter / 10);
	}

	else if (_timeCounter > 199 && _timeCounter < 300)
	{
		_onScreenText = L"Scale";
		return Matrix::ScaleMatrix((float)_timeCounter / 100, (float)_timeCounter / 100, (float)_timeCounter / 100);
	}

	else if (_timeCounter > 299 && _timeCounter < 400)
	{
		_onScreenText = L"Rotate Z";
		return Matrix::RotationMatrix(0, 0, (float)5 * (_timeCounter - 299));
	}

	else if (_timeCounter > 399 && _timeCounter < 500)
	{
		_onScreenText = L"Rotate X";
		return Matrix::RotationMatrix(5 * (float)(_timeCounter - 399), 0, 0);
	}

	else if (_timeCounter > 499 && _timeCounter < 600)
	{
		_onScreenText = L"Rotate Y";
		return Matrix::RotationMatrix(0, 5 * (float)(_timeCounter - 499), 0);
	}

	else
	{
		_onScreenText = L"Rotate X and Y";
		Matrix temp = Matrix::RotationMatrix(0, (float)2.5 * (_timeCounter - 599), 0) * Matrix::RotationMatrix((float)1.2 * (_timeCounter - 599),0, 0);
		return temp;
	}
}

/**
SwitchTypeCheck checks our current renter types and when we get to the end of
our timer it changes to the next type of rendering.
For example:
Using a wireframe and no culling then changes to culling and a wireframe.
Culling and a wireframe then changes to culling with no wireframe
and finally we change to be using lights also.
*/
void Rasteriser::SwitchTypeCheck()
{
	if (_timeCounter > 599 && !cull && wireframe)
	{
		_timeCounter = 0;
		cull = true;
	}

	if (_timeCounter > 599 && cull && wireframe)
	{
		_timeCounter = 0;
		wireframe = false;
	}

	if (_timeCounter > 599 && cull && !wireframe)
	{
		//_timeCounter = 0;
		lights = true;
	}
}





/******************************************/
/// ONSCREEN DISPLAY
/******************************************/

/**
	DisplayText is used to display the current render type on screen so that the viewer knows whats happening
*/
void Rasteriser::DisplayText(Bitmap &bitmap)
{
	TextOut(bitmap.GetDC(), 20, 10, _onScreenRenderType, (int)wcslen(_onScreenRenderType));
	TextOut(bitmap.GetDC(), 20, 25, _onScreenCullType, (int)wcslen(_onScreenCullType));
	TextOut(bitmap.GetDC(), 20, 40, _onScreenText, (int)wcslen(_onScreenText));
	TextOut(bitmap.GetDC(), 20, 55, _onScreenLightType, (int)wcslen(_onScreenLightType));
	TextOut(bitmap.GetDC(), 20, 70, _onScreenPolyType, (int)wcslen(_onScreenPolyType));
}





/*
	Stuff I could do..
	* Change the GenerateViewMatrix to return a matrix (this way we can save the matrix anywhere rather than having to have viewMatrix defined in the main header file)
	* Change the GeneratePerspectiveMatrix to return a matrix (this way we can save the matrix anywhere rather than having to have perspectiveMatrix defined in the main header file)
*/