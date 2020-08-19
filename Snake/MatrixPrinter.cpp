#pragma once
#include "pch.h"
#include "MatrixPrinter.h"


using namespace Screen;

MatrixPrinter::MatrixPrinter(
	char** initialBuffer,
	uint16_t initialRowCount,
	uint16_t initialColumnCount,
	Coordinate initialStartPosition
) {
	columnCount = initialColumnCount;
	rowCount = initialRowCount;
	startPosition = initialStartPosition;
	
	buffer = new char*[rowCount];
	for (int i = 0; i < rowCount; i++) {
		buffer[i] = new char[columnCount + 1];
		buffer[i][columnCount] = 0;
		strcpy(buffer[i], (const char*) initialBuffer[i]);
	}
}

MatrixPrinter::~MatrixPrinter() {
	for (int i = 0; i < rowCount; i++)
		delete[] buffer[i];

	delete[] buffer;
}

void MatrixPrinter::WriteAllToScreen() {	
	uint16_t finalYPosition = startPosition.y + rowCount;

	for (currentPosition.y = startPosition.y; currentPosition.y < finalYPosition; currentPosition.y++)
	{
		currentPosition.x = startPosition.x;
		PrintRow();
	}
}

void Screen::MatrixPrinter::Edit(int xCoordinate, int yCoordinate, char newValue) {
	if (0 <= xCoordinate && xCoordinate < columnCount
		&& 0 <= yCoordinate && yCoordinate < rowCount) {
		buffer[yCoordinate][xCoordinate] = newValue;

		currentPosition.x = xCoordinate + startPosition.x;
		currentPosition.y = yCoordinate + startPosition.y;

		Screen::ConsoleIO::GotoXY(currentPosition);
		putchar(newValue);
	}
}

char* MatrixPrinter::DetermineCurrentRow() {
	return buffer[currentPosition.y - startPosition.y];
}

void MatrixPrinter::PrintRow() {
	char* currentRow = DetermineCurrentRow();
	Screen::ConsoleIO::GotoXY(currentPosition);

	PrintCurrentRow(currentRow);
}


void MatrixPrinter::PrintCurrentRow(char* currentRow) {
	for (int position = 0; position < columnCount; position++)
	{
		putchar(currentRow[position]);
	}
}