#pragma once
class Rgb
{
public:
	Rgb();
	Rgb(int red, int green, int blue);

	int GetRed();
	int GetGreen();
	int GetBlue();

	void Set(int red, int green, int blue);
	void SetRed(int red);
	void SetGreen(int green);
	void SetBlue(int blue);

private:
	int _red;
	int _green;
	int _blue;
};

