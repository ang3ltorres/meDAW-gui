#include "gui/widget.hpp"

using namespace gui;
using namespace glm;

bool gui::repaintNextFrame = false;
std::vector<EventListener*> Widget::eventSubs;

Widget::Widget(const glm::ivec2& pos, const glm::ivec2& size, const std::string& name)
: pos(pos), size(size), name(name), shapes()
{}

Pane::Pane()
: Widget({0, 0}, {0, 0}, "")
{}

Button::Button(const glm::ivec2& pos, const glm::ivec2& size, std::function<void()> callback)
: Widget(pos, size, ""), callback(callback), cursorInside(false), active(false)
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
	size = {(Graphics::width * 0.2f) / 2, Graphics::height * 0.1f};
	reinterpret_cast<shape::Rectangle*>(shapes[0])->repaint(size.x, size.y, 8, 8, (active) ? palette::hex::pink : palette::hex::purple, palette::hex::black);
	shapes[0]->sprite->dst = {pos.x, pos.y, size.x, size.y};
	shapes[0]->sprite->updateModel();
	shapes[0]->sprite->batch();
	shapes[0]->sprite->texture->draw();
}

void Button::EVENT_CURSOR_MOVED()
{
	cursorInside =
		(unsigned)(Event::cursor.x - pos.x) <= (unsigned)size.x &&
		(unsigned)(Event::cursor.y - pos.y) <= (unsigned)size.y;
}

void Button::EVENT_MOUSE_BUTTON()
{
	if (!active and cursorInside and Event::mouseStates[GLFW_MOUSE_BUTTON_1])
	{
		draw();
		repaintNextFrame = true;
		active = true;
		callback();
	}

	if (active and !Event::mouseStates[GLFW_MOUSE_BUTTON_1])
	{
		draw();
		repaintNextFrame = true;
		active = false;
	}
}

