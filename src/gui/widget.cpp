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

Button::Button(const glm::ivec2& pos, const glm::ivec2& size, std::function<void()> callback, std::initializer_list<std::string> icon)
: Widget(pos, size, ""), callback(callback), cursorInside(false), active(false), icon(icon)
{
	
	if (icon.size() == 0)
		shapes.push_back(new shape::Rectangle{});
	else
	{
		shapes.push_back(new shape::SVG{*icon.begin()});
		shapes.push_back(new shape::SVG{*(icon.begin()+1)});
		shapes.push_back(new shape::SVG{*(icon.begin()+2)});
	}

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
	static int index = 0;

	if (icon.size() == 0)
	{
		reinterpret_cast<shape::Rectangle*>(shapes[0])->repaint(size.x, size.y, 0, 0, (active) ? palette::hex::pink : palette::hex::purple, palette::hex::black);
	}
	else
	{
		if (active)
		{
			reinterpret_cast<shape::SVG*>(shapes[1])->repaint(size.x, size.y);
			index = 1;
		}
		else if (cursorInside)
		{
			reinterpret_cast<shape::SVG*>(shapes[2])->repaint(size.x, size.y);
			index = 2;
		}
		else
		{
			reinterpret_cast<shape::SVG*>(shapes[0])->repaint(size.x, size.y);
			index = 0;
		}
	}

	shapes[index]->sprite->dst = {pos.x, pos.y, size.x, size.y};
	shapes[index]->sprite->updateModel();
	shapes[index]->sprite->batch();
	shapes[index]->sprite->texture->draw();
}

void Button::EVENT_CURSOR_MOVED()
{
	static bool oldCursorInside = false;
	oldCursorInside = cursorInside;

	cursorInside =
		(unsigned)(Event::cursor.x - pos.x) <= (unsigned)size.x &&
		(unsigned)(Event::cursor.y - pos.y) <= (unsigned)size.y;

	if (oldCursorInside != cursorInside)
	{
		draw();
		repaintNextFrame = true;
	}
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

