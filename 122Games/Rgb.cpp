#include "Rgb.h"

Rgb::Rgb()
{
	Set(0, 0, 0);
}


Rgb::Rgb(int red, int green, int blue)
{
	Set(red, green, blue);
}


void Rgb::Set(int red, int green, int blue)
{
	_red = red;
	_green = green;
	_blue = blue;
}


int Rgb::GetRed()
{
	return _red;
}


int Rgb::GetGreen()
{
	return _green;
}


int Rgb::GetBlue()
{
	return _blue;
}


void Rgb::SetRed(int red)
{
	_red = red;
}


void Rgb::SetGreen(int green)
{
	_green = green;
}


void Rgb::SetBlue(int blue)
{
	_blue = blue;
}
