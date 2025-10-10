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
	shape = new shape::Rectangle{300, 300, 20, 4};
}

TopBar::~TopBar()
{
	delete shape;
}

void TopBar::draw()
{
	shape->sprite->batch();
	shape->sprite->texture->draw();
}

void TopBar::update()
{
}

std::vector<Pane*> Editor::panes;

void Editor::initialize()
{
	panes.push_back(new TopBar{});

	// Set generic update callback
	Event::callback = [](){

		Editor::update();
	};
}

void Editor::finalize()
{
	
}

void Editor::update()
{
	Graphics::clearScreen({255, 143, 119, 255});

	for (const auto& i : panes)
		i->draw();

	glfwSwapBuffers(Graphics::window);
}
