#pragma once

class LedMatrix;

class MainUi
{
public:
	MainUi();

	LedMatrix* GetLedMatrix();

private:
	LedMatrix* _ledMatrix;
};

