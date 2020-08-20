#pragma once
#include "ConsoleIO.h"

namespace Screen
{
	class MatrixPrinter
	{
		char** buffer;
		uint16_t rowCount;
		uint16_t columnCount;

		Coordinate currentPosition;
		Coordinate startPosition;

	public:
		MatrixPrinter(
			char** buffer,
			uint16_t rowCount,
			uint16_t columnCount,
			Coordinate initialStartPosition
		);
		~MatrixPrinter();
		void WriteAllToScreen();
		void Edit(int xCoordinate, int yCoordinate, char newValue);

	private:
		char* DetermineCurrentRow();
		void PrintRow();
		void PrintCurrentRow(char* currentRow);
	};
}