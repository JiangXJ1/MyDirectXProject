#include "Color.h"

namespace Engine {
	Color::Color() : r(1), g(1), b(1), a(1)
	{

	}

	Color::Color(const Color & color)
		: r(color.r), g(color.g), b(color.b), a(color.a)
	{
	}

	Color::Color(float tmpr, float tmpg, float tmpb, float tmpa)
		: r(tmpr), g(tmpg), b(tmpb), a(tmpa)
	{
	}

	Color::~Color()
	{
	}
}
