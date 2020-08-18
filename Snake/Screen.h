#pragma once
#include <iostream>
#include "Coordinate.h"
#include "ConsoleIO.h"

namespace Screen
{
	const static Coordinate ORIGIN = { 0,0 };

	static inline void writeToXY(Coordinate coord, unsigned char c)
	{
		ConsoleIO::GotoXY(coord);
		putchar(c);
	}
};