#include "Matrix.h"

/// Constructors
Matrix::Matrix()
{
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			matrixarray[row][col] = 0;
		}
	}	
}

// Copy constructor implementation
Matrix::Matrix(const Matrix& matrixToCopy)
{
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			matrixarray[row][col] = matrixToCopy.matrixarray[row][col];
		}
	}
}

/// Destructor
Matrix::~Matrix()
{
}

/// Accessors
// GET
float Matrix::GetM(const int row, const int column) const
{
	return matrixarray[row][column];
}
// SET
void Matrix::SetM(const int row, const int column, const float value)
{
	matrixarray[row][column] = value;
}


/// Operators
// Matrix A + Matrix B
const Matrix Matrix::operator+(const Matrix& rhs) const
{
	Matrix returnValue;
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			returnValue.SetM(row, col, this->GetM(row, col) + rhs.GetM(row, col));
		}
	}
	return returnValue;
}

// Matrix A - Matrix B
const Matrix Matrix::operator-(const Matrix& rhs) const
{
	Matrix returnValue;
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			returnValue.SetM(row, col, this->GetM(row, col) - rhs.GetM(row, col));
		}
	}
	return returnValue;
}

// Matrix A * Matrix B
const Matrix Matrix::operator*(const Matrix &other) const
{
	Matrix TempMatrix;
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			float Value = 0;
			for (int looper = 0; looper < MATRIX_COL; looper++)
			{
				Value += this->GetM(row, looper) * other.GetM(looper, col);
			}
			TempMatrix.SetM(row, col, Value);
		}
	}
	return TempMatrix;
}

// Matrix A / Matrix B
const Matrix Matrix::operator/(const Matrix &other) const
{
	Matrix TempMatrix;
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			TempMatrix.SetM(row, col, this->GetM(row, col) / other.GetM(row, col));
		}
	}
	return TempMatrix;
}

// Matrix A = Matrix B
Matrix& Matrix::operator=(const Matrix &rhs)
{
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			matrixarray[row][col] = rhs.matrixarray[row][col];
		}
	}
	return *this;
}

// Matrix A * Vertex B
const Vertex Matrix::operator*(const Vertex & other) const
{
	Vertex TempVertex;

	TempVertex.SetX(this->GetM(0, 0) * other.GetX() + this->GetM(0, 1) * other.GetY() + this->GetM(0, 2) * other.GetZ() + this->GetM(0, 3) * other.GetW());
	TempVertex.SetY(this->GetM(1, 0) * other.GetX() + this->GetM(1, 1) * other.GetY() + this->GetM(1, 2) * other.GetZ() + this->GetM(1, 3) * other.GetW());
	TempVertex.SetZ(this->GetM(2, 0) * other.GetX() + this->GetM(2, 1) * other.GetY() + this->GetM(2, 2) * other.GetZ() + this->GetM(2, 3) * other.GetW());
	TempVertex.SetW(this->GetM(3, 0) * other.GetX() + this->GetM(3, 1) * other.GetY() + this->GetM(3, 2) * other.GetZ() + this->GetM(3, 3) * other.GetW());

	return TempVertex;
}


/// Modifiers 
// Matrix A = Matrix B * Scalar
const Matrix Matrix::ScaleBy(int scale)
{
	Matrix TempMatrix;
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			TempMatrix.matrixarray[row][col] = this->matrixarray[row][col] * scale;
		}
	}
	return TempMatrix;
}


/// Change instance into a matrix type
// Example: MakeIntoTransformMatrix(2,2,2);			-> Changes a matric instance into a matrix used to move point +2 on x, +2 on y, and +2 on z
void Matrix::MakeIntoTransformMatrix(float x, float y, float z)
{
	SetM(0, 3, x);
	SetM(1, 3, y);
	SetM(2, 3, z);

	SetM(0, 0, 1);
	SetM(1, 1, 1);
	SetM(2, 2, 1);
	SetM(3, 3, 1);
}

// Example: MakeIntoScaleMatrix(1.01, 1.01, 1.01);	-> Changes a matric instance into a matrix used to move point x+0.1x y+0.1y and z+0.1z
void Matrix::MakeIntoScaleMatrix(float x, float y, float z)
{
	SetM(0, 0, x);
	SetM(1, 1, y);
	SetM(2, 2, z);
	SetM(3, 3, 1);
}

// Example: MakeIntoRotationMatrix(0, 0, 1);		-> Changes a matric instance into a matrix used to move point on 0 x rotation, 0 y rotation and 1 degree z rotation
void Matrix::MakeIntoRotationMatrix(float x, float y, float z)
{
	Matrix XMatrix;
	XMatrix.SetM(0, 0, (float)1);
	XMatrix.SetM(1, 1, (float)cos(x* (M_PI / 180.0)));
	XMatrix.SetM(1, 2, (float)-sin(x* (M_PI / 180.0)));
	XMatrix.SetM(2, 1, (float)sin(x* (M_PI / 180.0)));
	XMatrix.SetM(2, 2, (float)cos(x* (M_PI / 180.0)));
	XMatrix.SetM(3, 3, (float)1);


	Matrix YMatrix;
	YMatrix.SetM(1, 1, (float)1);
	YMatrix.SetM(0, 0, (float)cos(y* (M_PI / 180.0)));
	YMatrix.SetM(0, 2, (float)sin(y* (M_PI / 180.0)));
	YMatrix.SetM(2, 0, (float)-sin(y* (M_PI / 180.0)));
	YMatrix.SetM(2, 2, (float)cos(y* (M_PI / 180.0)));
	YMatrix.SetM(3, 3, (float)1);

	Matrix ZMatrix;
	ZMatrix.SetM(0, 0, (float)cos(z* (M_PI / 180.0)));
	ZMatrix.SetM(0, 1, (float)-sin(z* (M_PI / 180.0)));
	ZMatrix.SetM(1, 0, (float)sin(z* (M_PI / 180.0)));
	ZMatrix.SetM(1, 1, (float)cos(z* (M_PI / 180.0)));
	ZMatrix.SetM(2, 2, (float)1);
	ZMatrix.SetM(3, 3, (float)1);

	Matrix RMatrix = XMatrix*YMatrix*ZMatrix;
	for (int row = 0; row < MATRIX_ROW; row++)
	{
		for (int col = 0; col < MATRIX_COL; col++)
		{
			matrixarray[row][col] = RMatrix.matrixarray[row][col];
		}
	}
}


/// Return a matrix type
// Example: TransformMatrix(2,2,2);			-> Returns a Matrix used to move point +2 on x, +2 on y, and +2 on z
Matrix Matrix::TransformMatrix(float x, float y, float z)
{
	static Matrix TMatrix;
	TMatrix.SetM(0, 3, x);
	TMatrix.SetM(1, 3, y);
	TMatrix.SetM(2, 3, z);

	TMatrix.SetM(0, 0, 1);
	TMatrix.SetM(1, 1, 1);
	TMatrix.SetM(2, 2, 1);
	TMatrix.SetM(3, 3, 1);
	return TMatrix;
}

// Example: ScaleMatrix(1.01, 1.01, 1.01);	-> Returns a Matrix used to move point x+0.1x y+0.1y and z+0.1z
Matrix Matrix::ScaleMatrix(float x, float y, float z)
{
	static Matrix SMatrix;
	SMatrix.SetM(0, 0, x);
	SMatrix.SetM(1, 1, y);
	SMatrix.SetM(2, 2, z);
	SMatrix.SetM(3, 3, 1);
	return SMatrix;
}

// Example: RotationMatrix(0, 0, 1);		-> Returns a Matrix used to move point on 0 x rotation, 0 y rotation and 1 degree z rotation
Matrix Matrix::RotationMatrix(float x, float y, float z)
{
	Matrix XMatrix;

	//XMatrix.SetM(0, 0, (float)cos(x* (M_PI / 180.0)));
	//XMatrix.SetM(0, 1, (float)-sin(x* (M_PI / 180.0)));
	//XMatrix.SetM(1, 0, (float)sin(x* (M_PI / 180.0)));
	//XMatrix.SetM(1, 1, (float)cos(x* (M_PI / 180.0)));
	//XMatrix.SetM(2, 2, (float)1);
	//XMatrix.SetM(3, 3, (float)1);

	XMatrix.SetM(0, 0, (float)1);
	XMatrix.SetM(1, 1, (float)cos(x* (M_PI / 180.0)));
	XMatrix.SetM(1, 2, (float)-sin(x* (M_PI / 180.0)));
	XMatrix.SetM(2, 1, (float)sin(x* (M_PI / 180.0)));
	XMatrix.SetM(2, 2, (float)cos(x* (M_PI / 180.0)));
	XMatrix.SetM(3, 3, (float)1);


	Matrix YMatrix;
	YMatrix.SetM(1, 1, (float)1);
	YMatrix.SetM(0, 0, (float)cos(y* (M_PI / 180.0)));
	YMatrix.SetM(0, 2, (float)sin(y* (M_PI / 180.0)));
	YMatrix.SetM(2, 0, (float)-sin(y* (M_PI / 180.0)));
	YMatrix.SetM(2, 2, (float)cos(y* (M_PI / 180.0)));
	YMatrix.SetM(3, 3, (float)1);

	Matrix ZMatrix;

	//ZMatrix.SetM(0, 0, (float)1);
	//ZMatrix.SetM(1, 1, (float)cos(z* (M_PI / 180.0)));
	//ZMatrix.SetM(1, 2, (float)-sin(z* (M_PI / 180.0)));
	//ZMatrix.SetM(2, 1, (float)sin(z* (M_PI / 180.0)));
	//ZMatrix.SetM(2, 2, (float)cos(z* (M_PI / 180.0)));
	//ZMatrix.SetM(3, 3, (float)1);
	ZMatrix.SetM(0, 0, (float)cos(z* (M_PI / 180.0)));
	ZMatrix.SetM(0, 1, (float)-sin(z* (M_PI / 180.0)));
	ZMatrix.SetM(1, 0, (float)sin(z* (M_PI / 180.0)));
	ZMatrix.SetM(1, 1, (float)cos(z* (M_PI / 180.0)));
	ZMatrix.SetM(2, 2, (float)1);
	ZMatrix.SetM(3, 3, (float)1);

	Matrix RMatrix = XMatrix*YMatrix*ZMatrix;

	return RMatrix;
}