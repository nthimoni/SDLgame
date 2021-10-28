#ifndef TOOLS_HPP
# define TOOLS_HPP

class Vector2
{
	public:
		Vector2();
		Vector2(int x, int y);
		int x;
		int y;
};

struct Vec2f
{
	float x;
	float y;
};

bool XOR(bool a, bool b);
int mili_to_sec(int time);
float mili_to_sec_float(int time);

#endif
