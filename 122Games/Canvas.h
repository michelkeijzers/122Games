#pragma once
#include "Rgb.h"

class Canvas
{
public:
	Canvas();

	static const int MAX_X = 12;
	static const int MAX_Y = 12;

	Rgb GetPixel(int x, int y);
	bool IsInvalidated(int x, int y);
	
	void SetPixel(int x, int y, int red, int green, int blue);

	void ResetInvalidatedPixels();

private:
	Rgb _pixels[MAX_X][MAX_Y];
	bool _invalidated[MAX_X][MAX_Y];
};
