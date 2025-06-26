#pragma once
#include "gui/gui.hpp"
#include "gui/shapes.hpp"
#include "pch.hpp"

namespace gui::widget
{
	class Button : public Widget
	{
	public:
		Button(glm::ivec2 pos, glm::uvec2 size, unsigned char type, std::function<void()> function);
		Button(const Button&) = delete;
		~Button();

		void draw() override;

		gui::shape::Rectangle *rect;
		std::function<void()> function;
		unsigned char type;
	};
}