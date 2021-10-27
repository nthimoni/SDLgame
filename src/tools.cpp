#include "tools.hpp"

Vector2::Vector2() : x(0), y(0)
{
}

Vector2::Vector2(int p_x, int p_y) : x(p_x), y(p_y)
{
}

bool XOR(bool a, bool b)
{
	return (a && !b) || (!a && b);
}

int mili_to_sec(int time)
{
	return (time / 1000);
}
float mili_to_sec_float(int time)
{
	return (time / 1000.0f);
}
