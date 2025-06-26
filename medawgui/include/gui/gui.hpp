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

		std::vector<gui::Texture*> texture;
		glm::ivec2 pos;
		glm::uvec2 size;

		virtual void draw() = 0;
	};

	struct Pane
	{
		std::vector<Widget> widget;
		glm::ivec2 pos;
		glm::uvec2 size;
	};

	void initialize();
	void finalize();

	extern std::vector<Pane> pane;
}
