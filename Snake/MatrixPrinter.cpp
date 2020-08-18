#include "pch.h"
#include "MatrixPrinter.h"

inline void MatrixPrinter::WriteToScreen(
	Coordinate startPosition = Screen::ORIGIN
) {
	currentPosition = startPosition;
	
	uint16_t finalYPosition = startPosition.y + height;
	for (currentPosition.y = startPosition.y; currentPosition.y < finalYPosition; currentPosition.y++)
	{
		currentPosition.x = startPosition.x;
		PrintRow();
	}
}

inline char* MatrixPrinter::DetermineCurrentRow() {
	return buffer[currentPosition.y - startPosition.y];
}

inline void MatrixPrinter::PrintRow() {
	char* currentRow = DetermineCurrentRow();
	Screen::ConsoleIO::GotoXY(currentPosition);

	PrintCurrentRow(currentRow);
}


inline void MatrixPrinter::PrintCurrentRow(char* currentRow) {
	for (int position = 0; position < width; position++)
	{
		putchar(currentRow[position]);
		position++;
	}
}