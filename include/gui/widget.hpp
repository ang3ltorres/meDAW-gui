#pragma once

#include "gui/shapes.hpp"

namespace gui
{
	struct EventListener
	{
		virtual void EVENT_CURSOR_MOVED() = 0;
		virtual void EVENT_MOUSE_BUTTON() = 0;
	};

	struct Widget
	{
		Widget(const glm::ivec2& pos, const glm::ivec2& size, const std::string& name);
		Widget(const Widget&) = delete;
		virtual ~Widget() = default;

		glm::ivec2 pos;
		glm::ivec2 size;
		std::string name;
		std::vector<gui::shape::Shape*> shapes;

		virtual void draw() = 0;
		static std::vector<EventListener*> eventSubs;
	};

	struct Pane : public Widget
	{
		Pane();
		Pane(const Pane&) = delete;
		virtual ~Pane() = default;
		
		std::vector<Widget*> widgets;
		gui::shape::Rectangle rect;
	};

	struct Button : public Widget, public EventListener
	{
		Button(const glm::ivec2& pos, const glm::ivec2& size, std::function<void()> callback);
		Button(const Button&) = delete;
		virtual ~Button() override;

		std::function<void()> callback;
		bool cursorInside;

		virtual void draw() override;
		virtual void EVENT_CURSOR_MOVED() override;
		virtual void EVENT_MOUSE_BUTTON() override;
	};
}
