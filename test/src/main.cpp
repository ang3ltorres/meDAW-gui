#include "graphics.hpp"

int main()
{
	unsigned int width = 1280;
	unsigned int height = 720;
	
	gui::Graphics::initialize(width, height, "OpenGL");
	
	// gui::RenderTexture *renderTexture = new gui::RenderTexture{800, 600};

	gui::shape::Rectangle *rect = new gui::shape::Rectangle(50, 50, 10, 4);

	// renderTexture->dst.z *= 1;
	// renderTexture->dst.w *= 1;
	// renderTexture->updateModel();

	// svgSprite->dst.z *= 4;
	// svgSprite->dst.w *= 4;
	// svgSprite->updateModel();

	while (!gui::Graphics::shouldClose())
	{
		// Update logic
		// svgSprite->dst.x += 1;
		// svgSprite->updateModel();

		if (Input::keyboardStates[GLFW_KEY_ESCAPE])
			gui::Graphics::forceClose = true;

		// Render to target
		// gui::Graphics::setRenderTexture(renderTexture);
		// gui::Graphics::clearScreen({0, 255, 0});

		// Render to default "canvas"
		gui::Graphics::setRenderTexture();
		gui::Graphics::clearScreen({255, 143, 119});
		
		// renderTexture->batch();
		// renderTexture->texture->draw();

		// svgSprite->batch();
		// svgSprite->texture->draw();

		rect->sprite->batch();
		rect->sprite->texture->draw();

		gui::Graphics::endFrame();
	}

	delete rect;
	// delete renderTexture;

	gui::Graphics::finalize();
	return 0;
}