#include "gui/editor.hpp"

using namespace gui;
using namespace glm;

TransportBar::TransportBar()
{
	
}

TransportBar::~TransportBar()
{

}

ClockDisplays::ClockDisplays()
{
	
}

ClockDisplays::~ClockDisplays()
{

}

ModeSelector::ModeSelector()
{
	
}

ModeSelector::~ModeSelector()
{

}

TopBar::TopBar()
{
	rect = new shape::Rectangle{};
	rect->rebuild(200, 200, 8, 4, palette::hex::dark, palette::hex::pink);
}

TopBar::~TopBar()
{
	delete rect;
}

void TopBar::draw()
{
	rect->sprite->batch();
	rect->sprite->texture->draw();
}

void TopBar::update()
{
	rect->rebuild(200, 200, 8, 4, palette::hex::dark, palette::hex::pink);
}

std::vector<Pane*> Editor::panes;

void Editor::initialize()
{
	panes.push_back(new TopBar{});

	// First draw
	Editor::update();

	// Set generic update callback
	Event::updateCallback = &Editor::update;
}

void Editor::finalize()
{
	
}

void Editor::update()
{
	Graphics::clearScreen({255, 255, 255, 255});

	for (const auto& i : panes)
	{
		i->update();
		i->draw();
	}

	Graphics::drawBuffer();
}
