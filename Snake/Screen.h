#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>

typedef uint16_t ushort;

namespace Screen
{
	// Used mainly for console io. Makes function inputs much faster!
	struct Coordinate
	{
		ushort x = 0, y = 0;

		Coordinate() { x = 0; y = 0; }
		Coordinate(long x0, long y0) { x |= x0; y |= y0; }

		bool operator==(Coordinate b)
		{
			return (x == b.x && y == b.y);
		}

		Coordinate operator=(Coordinate b)
		{
			x += b.x;
			y += b.y;
			return { x,y };
		}
	};

	const Coordinate ORIGIN = { 0,0 };

	// Turning cursor on/off
	inline void turnOffCursor()
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = FALSE;

		SetConsoleCursorInfo(h, &info);
	}
	inline void turnOnCursor()
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = TRUE;

		SetConsoleCursorInfo(h, &info);
	}

	// Functions concerning coordinates on the screen
	inline void gotoXY(Coordinate coord) // Sets screen coordinates to the coordinate passed.
	{
		HANDLE h; _COORD c;
		fflush(stdout);

		c.X = coord.x; c.Y = coord.y;

		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, c);
	}

	// Returns the screen to a blank state
	inline void resetScreen()
	{
		system("cls");
		gotoXY(ORIGIN);
	}

	// Force screen size in pixels
	inline void changeScreenSize(ushort x, ushort y)
	{
		HWND consoleWindow = GetConsoleWindow();
		RECT screenPosition;
		GetWindowRect(consoleWindow, &screenPosition);

		resetScreen();
		MoveWindow(consoleWindow, screenPosition.left, screenPosition.top, x, y, TRUE);
	}

	inline void writeToXY(Coordinate coord, unsigned char c)
	{
		gotoXY(coord);
		putchar(c);
	}
	inline void writeSeries(Coordinate coordArr[], char chArr[], int numberOfBytes)
	{
		for (int i = 0; i < numberOfBytes; i++)
			writeToXY(coordArr[i], chArr[i]);
	}
	inline void writeToScreen(char **matrix, ushort width, ushort height, Coordinate startPosition = { 0,0 })
	// Assumes that matrix is a suitably large matrix such that it contains at least "height" rows each at least "width" wide.
	// Assumes that startPosition is a reasonable/legal coordinate on the screen.
	{
		Coordinate currentPosition;
		ushort &x = currentPosition.x, &y = currentPosition.y;
		ushort &x0 = startPosition.x, &y0 = startPosition.y;
		char* currentRow;

		for (y = y0; y < y0 + height; y++)
		{
			x = x0;
			gotoXY(currentPosition);
			currentRow = matrix[y - y0];

			while (x < x0 + width)
			{
				putchar(currentRow[x - x0]);
				x++;
			}
		}
	}
	inline void writeToBuffer(char **buffer, char** matrix, ushort width, ushort height, Coordinate startPosition = { 0,0 })
	// Assumes that matrix is a suitably large matrix such that it contains at least "height" rows each at least "width" wide.
	// Assumes that startPosition is a reasonable/legal coordinate on the screen.
	{
		Coordinate currentPosition;
		ushort &x = currentPosition.x, &y = currentPosition.y;
		ushort &x0 = startPosition.x, &y0 = startPosition.y;
		char* currentRow;

		for (y = y0; y < y0 + height; y++)
		{
			x = x0;
			currentRow = matrix[y - y0];

			while (x < x0 + width)
			{
				buffer[y - y0][x - x0] = currentRow[x - x0];
				x++;
			}
		}
	}
};