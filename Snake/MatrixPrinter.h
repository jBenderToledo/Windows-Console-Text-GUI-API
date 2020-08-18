#pragma once
#include "ConsoleIO.h"
#include "Screen.h"

class MatrixPrinter
{
	char** buffer;
	uint16_t rowCount;
	uint16_t columnCount;

	Coordinate currentPosition;
	Coordinate startPosition;

public:
	MatrixPrinter(char** buffer, uint16_t rowCount, uint16_t columnCount);
	~MatrixPrinter();
	void WriteToScreen(Coordinate startPosition);

private:
	char* DetermineCurrentRow();
	void PrintRow();
	void PrintCurrentRow(char* currentRow);
};

