#include "pch.h"
#include "Coordinate.h"


Coordinate::Coordinate() {
	x = 0;
	y = 0;
}
Coordinate::Coordinate(long x0, long y0) {
	x |= x0;
	y |= y0;
}