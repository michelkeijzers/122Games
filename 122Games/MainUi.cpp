#include "MainUi.h"
#include "LedMatrix.h"

MainUi::MainUi()
{
	_ledMatrix = new LedMatrix();
}


LedMatrix* MainUi::GetLedMatrix()
{
	return _ledMatrix;
}