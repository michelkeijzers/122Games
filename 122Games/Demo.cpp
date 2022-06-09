#include <stdlib.h>

#include "Demo.h"
#include "Canvas.h"

/* virtual */ void Demo::Start()
{
}


/* virtual */ void Demo::Play()
{
	int intensity = _light ? 255 : 20;

	for (int i = 0; i < 200; i++)
	{
		int x = rand() % Canvas::MAX_X;
		int y = rand() % Canvas::MAX_Y;

		//for (int x = 0; x < Canvas::MAX_X; x++)
		//{
		//	for (int y = 0; y < Canvas::MAX_Y; y++)
		//	{
		_canvas.SetPixel(x, y, rand() % 255, rand() % 255, rand() % 255);
	//	}
	//}
	}

	_light = !_light;
}


/* virtual */ void Demo::HandleButton(int player, Game::EButton button)
{
}