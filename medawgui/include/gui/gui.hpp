#pragma once

#include "core/texture.hpp"

namespace gui
{
	class Widget
	{
	public:
		Widget(glm::ivec2 pos, glm::uvec2 size);
		Widget(const Widget&) = delete;
		~Widget() = default;

		glm::ivec2 pos;
		glm::uvec2 size;
		std::vector<gui::Texture*> texture;

		virtual void draw() = 0;
	};

	class Pane
	{
	public:
		Pane(const glm::ivec2& pos, const glm::uvec2& size, const std::string& name = "DEFAULT");

		glm::ivec2 pos;
		glm::uvec2 size;
		std::string name;
		std::vector<Widget> widget;
	};
}
