#pragma once
#include "windows.h"

class Bitmap
{

public:

	// Constructor
	Bitmap();

	// Deconstructor
	~Bitmap();

	// Get
	HDC			 GetDC() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const ;

	// Create
	bool		 Create(HWND hWnd, unsigned int width, unsigned int height); 
	
	// Clear
	void	     Clear(HBRUSH hBrush);
	void	     Clear(COLORREF colour);

private:
	HBITMAP			_hBitmap;
	HBITMAP			_hOldBitmap;
	HDC				_hMemDC;
	unsigned int	_width;
	unsigned int	_height;

	void DeleteBitmap();

};

