#include "gui/widget.hpp"

using namespace gui;
using namespace glm;

std::vector<EventListener*> Widget::eventSubs;

Widget::Widget(const glm::ivec2& pos, const glm::uvec2& size, const std::string& name)
: pos(pos), size(size), name(name), shapes()
{}

Pane::Pane()
: Widget({0, 0}, {0, 0}, "")
{}

Button::Button(const glm::ivec2& pos, const glm::uvec2& size, std::function<void()> callback)
: Widget(pos, size, ""), callback(callback)
{
	shapes.push_back(new shape::Rectangle{});

	// Subscribe to input events
	Widget::eventSubs.push_back(this);
}

Button::~Button()
{
	for (auto i : shapes)
		delete i;
}

void Button::draw()
{
	reinterpret_cast<shape::Rectangle*>(shapes[0])->repaint(size.x, size.y, 8, 2, palette::hex::green, palette::hex::orange);
	shapes[0]->sprite->dst = {pos.x, pos.y, size.x, size.y};
	shapes[0]->sprite->updateModel();
	shapes[0]->sprite->batch();
	shapes[0]->sprite->texture->draw();
}

void Button::EVENT_CURSOR_MOVED()
{
	std::println("EVENT_CURSOR_MOVED");
}

