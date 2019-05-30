#include "pch.h"
#include <iostream>
#include "Screen.h"

using namespace Screen;

namespace ScreenTest
{
	void checkerBoard(short x0, short y0)
	{
		char black = 0x20, white = 0xB2;

		for (int y = 0; y < 8; y++)
		{
			gotoXY(0 + x0, y + y0);
			for (int x = 0; x < 8; x++)
			{
				putchar(((x + y) % 2 == 0) ? black : white);
			}
		}
	}

	void checkerBoardV2(short x0, short y0)
	{
		char black = 0x20, white = 0xB2;

		for (int y = 0; y < 8; y++)
			for (int x = 0; x < 8; x++)
				writeAtXY(x + x0, y + y0, ((x + y) % 2 == 0) ? black : white);
	}

	char hexValOf(int i)
	{
		if (0x61 <= i && i <= 0x66)
			return (i & ~0x60) + 0x9;
		else if (0x41 <= i && i <= 0x46)
			return (i & ~0x40) + 0x9;
		else if (0x30 <= i && i <= 0x39)
			return (i & ~0x30);
		else
			return -1; // The sign being on means that an error has occurred.
	}

	char getHexValueFromUser()
	{
		int input;
		do
		{
			input = hexValOf(_getch());
		} while (input & 0x80);

		return input;
	}

	void putStrOnLine(const char* cstring, short lineNumber)
	{
		gotoXY(0, lineNumber);
		while (*cstring != 0)
		{
			_putch(*cstring);
			cstring++;
		}
	}

	struct basicCoord {
		short x = 0, y = 0;
	};

	void putHexValue(basicCoord &c, int ch)
	{
		if (0 <= ch && ch <= 9)
			writeAtXY(c.x, c.y, ch + 0x30);
		else if (10 <= ch && ch < 16)
			writeAtXY(c.x, c.y, ch + 0x41 - 10);
	}

	void printBoardsIndefinitely()
	{
		const char* prompt = "Input a pair of hex coordinates to print a checkerboard!";
		const char* continuePrompt = "Press a key to continue!";
		const char* eraseContinuePrompt = "                        ";
		basicCoord inputCoord, displayInputXLocation, displayInputYLocation,
			previousInputXLocation, previousInputYLocation;
		short promptHeight = 17 + 8 + 1;

		displayInputXLocation.y = promptHeight;
		displayInputXLocation.x = strlen(prompt) + 1;

		displayInputYLocation.y = promptHeight;
		displayInputYLocation.x = displayInputXLocation.x + 2;

		previousInputXLocation.y = promptHeight;
		previousInputXLocation.x = displayInputYLocation.x + 5;

		previousInputYLocation.y = promptHeight;
		previousInputYLocation.x = previousInputXLocation.x + 2;


		short &x = inputCoord.x, &y = inputCoord.y;
		turnOffCursor();

		putStrOnLine(prompt, promptHeight);
		do
		{
			x = getHexValueFromUser();
			putHexValue(displayInputXLocation, x);

			y = getHexValueFromUser();
			writeAtXY(displayInputXLocation.x + 1, displayInputXLocation.y, ',');
			putHexValue(displayInputYLocation, y);

			putStrOnLine(continuePrompt, promptHeight + 2);
			writeAtXY(x, y, 'X');
			_getch();
			putStrOnLine(eraseContinuePrompt, promptHeight + 2);

			checkerBoardV2(x, y);

			for (int x0 = 0; x0 < 3; x0++)
				writeAtXY(displayInputXLocation.x + x0, displayInputXLocation.y, ' ');

			putHexValue(previousInputXLocation, x);
			putHexValue(previousInputYLocation, y);
			writeAtXY(previousInputXLocation.x - 1, previousInputXLocation.y, '(');
			writeAtXY(previousInputYLocation.x - 1, previousInputYLocation.y, ',');
			writeAtXY(previousInputYLocation.x + 1, previousInputYLocation.y, ')');
		} while (true);
	}
};;


int main()
{
	ScreenTest::printBoardsIndefinitely();
};
