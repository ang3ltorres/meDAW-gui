#pragma once

#include "pch.hpp"

#include "core/drawable.hpp"
#include "core/glyph.hpp"

namespace gui
{
	class Font : public Drawable
	{
	public:
		Font(const char *fontPath, unsigned int fontSize);
		Font(const Font &) = delete;
		~Font();

		Glyph glyphs[96]; // Printable characters (32 - 127)
		unsigned int fontSize;
	};
}

