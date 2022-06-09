#ifdef WIN32

#include <iostream>
#include <string>

#include "Box.h"

int main()
{
	std::cout << "WIN APP: 122 GAMES BOX 0.1\n";
	std::cout << "  BY MIKESOFT\n\n";

	Box box;
	box.setup();
	while (true)
	{
		box.loop();
	}
}

#endif // WIN32
