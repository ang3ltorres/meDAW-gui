#pragma once

namespace gui
{
	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
		
		Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
		Color(const Color& color) = default;
		~Color() = default;
	};
}

