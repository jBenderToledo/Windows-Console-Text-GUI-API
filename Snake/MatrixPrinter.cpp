#include "pch.h"
#include "MatrixPrinter.h"

MatrixPrinter::MatrixPrinter(
	char** initialBuffer,
	uint16_t initialRowCount,
	uint16_t initialColumnCount
) {
	columnCount = initialColumnCount;
	rowCount = initialRowCount;
	
	buffer = new char[rowCount][columnCount];
}

MatrixPrinter::~MatrixPrinter() {

}

inline void MatrixPrinter::WriteToScreen(
	Coordinate startPosition = Screen::ORIGIN
) {
	currentPosition = startPosition;
	
	uint16_t finalYPosition = startPosition.y + rowCount;
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
	for (int position = 0; position < columnCount; position++)
	{
		putchar(currentRow[position]);
		position++;
	}
}