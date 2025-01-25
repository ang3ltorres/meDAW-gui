#pragma once

#include "graphics.hpp"

namespace gui::shape
{
	class RectangleRounded
	{
	public:
		RectangleRounded(unsigned int width, unsigned int height, unsigned int roundness, unsigned int thickness);
		RectangleRounded(const RectangleRounded&) = delete;
		~RectangleRounded();

		gui::Texture *texture;
		gui::Sprite  *sprite;
	};
}
