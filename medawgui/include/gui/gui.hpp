#pragma once

#include "gui/shapes.hpp"

namespace gui
{
	struct Widget
	{
		Widget(const glm::ivec2& pos, const glm::uvec2& size, const std::string& name);
		Widget(const Widget&) = delete;
		virtual ~Widget() = default;

		glm::ivec2 pos;
		glm::uvec2 size;
		std::string name;
		std::vector<gui::shape::Shape*> shapes;

		virtual void draw() = 0;
	};

	struct Pane : public Widget
	{
		Pane();
		Pane(const Pane&) = delete;
		virtual ~Pane() = default;
		
		std::vector<Widget*> widgets;
		gui::shape::Shape* shape;

		// Rearrenge internal widgets and draw them
		virtual void update() = 0;
	};
}
