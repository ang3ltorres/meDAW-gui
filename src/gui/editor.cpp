#include "gui/editor.hpp"

using namespace gui;
using namespace glm;

TransportBar::TransportBar()
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

	// First draw
	Editor::repaint();

	// Set generic update callback
	Event::updateCallback = &Editor::repaint;
}

void Editor::finalize()
{
	for (auto i : panes)
		delete i;
}

void Editor::repaint()
{
	Graphics::clearScreen(palette::rgb::darker);

	for (const auto& i : panes)
		i->draw();

	Graphics::drawBuffer();
}
