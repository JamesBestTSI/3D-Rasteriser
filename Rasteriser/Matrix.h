#pragma once
#include "Vertex.h"
#include <math.h>
//#include <initializer_list>


#define MATRIX_ROW 4
#define MATRIX_COL 4

# define M_PI           3.14159265358979323846

class Matrix
{
public:
	
	/// Default constructor
	Matrix();
	//Matrix(std::initializer_list<float> list);

	/// Copy constructor.  
	Matrix(const Matrix& matrixToCopy);

	/// Destructer
	~Matrix();

	/// Accessors
	float GetM(const int row, const int column) const;
	void SetM(const int row, const int column, const float value);

	/// Operators
	const Matrix operator+  (const Matrix& rhs) const;
	const Matrix operator-  (const Matrix& rhs) const;
	const Matrix operator*	(const Matrix &other) const;
	const Matrix operator/	(const Matrix &other) const;
	Matrix&		 operator=	(const Matrix &rhs);
	const Vertex operator*(const Vertex &other) const;

	/// Modifiers
	const Matrix ScaleBy(int scale);

	/// Create Matrix types
	// Changes 'Matrix' into a suitable matrix for Transforming position
	void MakeIntoTransformMatrix(float x, float y, float z);
	// Changes 'Matrix' into a suitable matrix for Resizing
	void MakeIntoScaleMatrix(float x, float y, float z);
	// Changes 'Matrix' into a suitable matrix for Rotateing
	void MakeIntoRotationMatrix(float x, float y, float z);

	/// Return Matrix types
	// Returns a suitable matrix for Transforming position
	static Matrix TransformMatrix(float x, float y, float z);
	// Returns a suitable matrix for Resizing
	static Matrix ScaleMatrix(float x, float y, float z);
	// Returns a suitable matrix for Rotateing
	static Matrix RotationMatrix(float x, float y, float z);

private:
	float matrixarray[MATRIX_ROW][MATRIX_COL];
};