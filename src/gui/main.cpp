#include "core/graphics.hpp"
#include "gui/editor.hpp"
// code --enable-features=UseOzonePlatform --ozone-platform=wayland
using namespace gui;

int main()
{
	unsigned int width = 1280;
	unsigned int height = 720;

	Graphics::initialize(width, height, "OpenGL");
	
	// Render to default "canvas"
	// Force firts draw to avoid bugs on Wayland and epilepsy
	Graphics::setRenderTexture();
	Graphics::drawBuffer();
	Editor::initialize();

	while (!Graphics::shouldClose())
	{
		if (Event::keyboardStates[GLFW_KEY_ESCAPE])
			Graphics::forceClose = true;

		if (repaintNextFrame)
			Editor::repaint();

		Graphics::pollEvents();
	}

	Editor::finalize();
	Graphics::finalize();
	return 0;
}