#include "MainUi.h"


MainUi::MainUi()
{
	
}


void MainUi::Initialize()
{
	_ledMatrix.Initialize(MAX_X, MAX_Y);

}


LedMatrix* MainUi::GetLedMatrix()
{
	return &_ledMatrix;
}
