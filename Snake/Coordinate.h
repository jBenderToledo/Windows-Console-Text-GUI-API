#pragma once

class Coordinate
{
public:
	unsigned short x = 0;
	unsigned short y = 0;
	Coordinate(long x0 = (long) 0, long y0 = (long) 0);
};

namespace Screen {
	const static Coordinate ORIGIN = Coordinate(0, 0);
}