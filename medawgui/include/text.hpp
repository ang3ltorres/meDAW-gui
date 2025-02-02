#pragma once

#include "pch.hpp"

#include "renderTexture.hpp"
#include "font.hpp"

namespace gui
{
	class Text
	{
	public:
		Text(gui::Font *font, const char *text);
		Text(const Text &) = delete;
		~Text();

		gui::Font *font;
		gui::RenderTexture *renderTexture;

		void render(const char *text);
	};
}

