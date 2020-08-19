#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "Coordinate.h"

namespace Screen
{
	class ConsoleIO
	{
	public:
		static void TurnOffCursor();
		static void TurnOnCursor();
		static void GotoXY(Coordinate position);
		static void writeToXY(Coordinate coord, unsigned char c);
	};
}
