#include "gui/editor.hpp"

using namespace gui;
using namespace glm;

TransportBar::TransportBar()
: buttonTest({0, 0}, {128, 64}, [](){std::println("HELLO WORLD");})
{
}

TransportBar::~TransportBar()
{

}

void TransportBar::draw()
{
	rect.repaint(Graphics::width * 0.2f, Graphics::height * 0.1f, 0, 0, palette::hex::green);
	
	rect.sprite->batch();
	rect.sprite->texture->draw();

	buttonTest.draw();
}

ClockDisplays::ClockDisplays()
{
	
}

ClockDisplays::~ClockDisplays()
{

}

void ClockDisplays::draw()
{
	rect.repaint(Graphics::width * 0.2f, Graphics::height * 0.1f, 0, 0, palette::hex::yellow);
	rect.sprite->dst.x += Graphics::width * 0.2f;
	rect.sprite->updateModel();

	rect.sprite->batch();
	rect.sprite->texture->draw();
}

ModeSelector::ModeSelector()
{
	
}

ModeSelector::~ModeSelector()
{

}

TopBar::TopBar()
{
}

TopBar::~TopBar()
{

}

void TopBar::draw()
{
	rect.repaint(Graphics::width, Graphics::height * 0.1f, 0, 0, palette::hex::dark);

	rect.sprite->batch();
	rect.sprite->texture->draw();

	transportBar.draw();
	clockDisplays.draw();
}

std::vector<Pane*> Editor::panes;

void Editor::initialize()
{
	panes.push_back(new TopBar{});

	repaintNextFrame = true;

	// First draw
	Editor::repaint();

	// Set generic update callback
	Event::updateCallback = &Editor::repaint;

	Event::cursorMovedCallback = &Editor::EVENT_CURSOR_MOVED;
	Event::mouseButtonCallback = &Editor::EVENT_MOUSE_BUTTON;
}

void Editor::finalize()
{
	for (auto i : panes)
		delete i;
}

void Editor::repaint()
{
	repaintNextFrame = false;
	Graphics::clearScreen(palette::rgb::darker);

	for (const auto& i : panes)
		i->draw();

	Graphics::drawBuffer();
}

void Editor::EVENT_MOUSE_BUTTON()
{
	for (auto& i : Widget::eventSubs)
		i->EVENT_MOUSE_BUTTON();
}

void Editor::EVENT_CURSOR_MOVED()
{
	for (auto& i : Widget::eventSubs)
		i->EVENT_CURSOR_MOVED();
}

