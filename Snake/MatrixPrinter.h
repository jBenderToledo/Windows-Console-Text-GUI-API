#pragma once
#include "ConsoleIO.h"
#include "Screen.h"

class MatrixPrinter
{
	char** buffer;
	uint16_t width;
	uint16_t height;

	Coordinate currentPosition;
	Coordinate startPosition;

public:
	void WriteToScreen(Coordinate startPosition);

private:
	char* DetermineCurrentRow();
	void PrintRow();
	void PrintCurrentRow(char* currentRow);
};

