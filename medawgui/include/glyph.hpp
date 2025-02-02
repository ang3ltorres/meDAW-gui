#pragma once

#include "pch.hpp"

namespace gui
{
	struct Glyph
	{
		glm::vec2 bearing;
		glm::vec2 size;
		glm::ivec2 atlasPos;
		float advance;
	};
}
