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
	mainShape = new shape::Rectangle{300, 300, 20, 4};
}

TopBar::~TopBar()
{
	delete mainShape;
}

void Editor::initialize()
{
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
	std::println("XD");
}
