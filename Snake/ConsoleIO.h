#pragma once
#include "pch.h"

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
		static void WriteToXY(Coordinate coord, unsigned char c);
	};
}
