#pragma once
#ifndef _COLOR_H
#define _COLOR_H
namespace Engine {
	class Color {
	public:
		float r, g, b, a;
	public:
		Color();
		Color(const Color& color);
		Color(float tmpr, float tmpg, float tmpb, float tmpa = 1);
		~Color();
	};
}

#endif // !_COLOR_H
