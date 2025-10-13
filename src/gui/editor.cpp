#include "gui/editor.hpp"

using namespace gui;
using namespace glm;

TransportBar::TransportBar()
{
}

TransportBar::~TransportBar()
{

}

void TransportBar::update()
{
	rect.rebuild(Graphics::width * 0.2f, Graphics::height * 0.1f, 0, 0, palette::hex::green);
}

void TransportBar::draw()
{
	rect.sprite->batch();
	rect.sprite->texture->draw();
}

ClockDisplays::ClockDisplays()
{
	
}

ClockDisplays::~ClockDisplays()
{

}

void ClockDisplays::update()
{
	rect.rebuild(Graphics::width * 0.2f, Graphics::height * 0.1f, 0, 0, palette::hex::yellow);
	rect.sprite->dst.x += Graphics::width * 0.2f;
	rect.sprite->updateModel();
}

void ClockDisplays::draw()
{
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

void TopBar::update()
{
	rect.rebuild(Graphics::width, Graphics::height * 0.1f, 0, 0, palette::hex::dark);
	transportBar.update();
	clockDisplays.update();
}

void TopBar::draw()
{
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
	Editor::update();

	// Set generic update callback
	Event::updateCallback = &Editor::update;
}

void Editor::finalize()
{
	for (auto i : panes)
		delete i;
}

void Editor::update()
{
	Graphics::clearScreen(palette::rgb::darker);

	for (const auto& i : panes)
	{
		i->update();
		i->draw();
	}

	Graphics::drawBuffer();
}
