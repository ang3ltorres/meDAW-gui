#pragma once

#include "pch.hpp"

namespace gui
{
	struct Glyph
	{
		glm::vec2 bearing;
		glm::vec2 size;
		glm::vec2 uvMin;
		glm::vec2 uvMax;
		float advance;
	};
}
