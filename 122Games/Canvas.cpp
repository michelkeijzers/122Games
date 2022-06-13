/*

#include "Canvas.h"

#include "Rgb.h"

Canvas::Canvas()
{
	ResetInvalidatedPixels();
}


Rgb Canvas::GetPixel(int x, int y)
{
	return _pixels[x][y];
}


void Canvas::SetPixel(int x, int y, int red, int green, int blue)
{
	Rgb rgb = GetPixel(x, y);
	if ((rgb.GetRed() != red) || (rgb.GetGreen() != green) || (rgb.GetBlue() != blue))
	{
		_pixels[x][y].Set(red, green, blue);
		_invalidated[x][y] = true;
	}
}


bool Canvas::IsPixelInvalidated(int x, int y)
{
	return _invalidated[x][y];
}


void Canvas::ResetInvalidatedPixels()
{
	for (int x = 0; x < Canvas::MAX_X; x++)
	{
		for (int y = 0; y < Canvas::MAX_Y; y++)
		{
			_invalidated[x][y] = false;
		}
	}
}

*/