#pragma once

#include "gui/shapes.hpp"

namespace gui
{
	class Widget
	{
	public:
		Widget(const glm::ivec2& pos, const glm::uvec2& size, const std::string& name);
		Widget(const Widget&) = delete;
		virtual ~Widget() = default;

		glm::ivec2 pos;
		glm::uvec2 size;
		std::string name;
		std::vector<gui::shape::Shape*> shapes;

		virtual void draw() = 0;
	};

	class Pane : public Widget
	{
	public:
		Pane(const Pane&) = delete;
		virtual ~Pane() override;
		
		std::vector<Widget*> widgets;

		// Rearrenge internal widgets and draw them
		virtual void update() = 0;
	};
}
