#include "graphics.hpp"

int main()
{
	unsigned int width = 1280;
	unsigned int height = 720;
	
	gui::Graphics::initialize(width, height, "OpenGL");
	
	gui::RenderTexture *renderTexture = new gui::RenderTexture{800, 600};

	gui::shape::Rectangle *rect = new gui::shape::Rectangle(50, 150, 10, 4);

	gui::Font *font = new gui::Font{"/home/angel/meDAW-res/mononoki-Regular.ttf", 90};

	gui::Text *text = new gui::Text{font, "EXAMPLE TEXTa"};

	// renderTexture->dst.z *= 1;
	// renderTexture->dst.w *= 1;
	// renderTexture->updateModel();

	// svgSprite->dst.z *= 4;
	// svgSprite->dst.w *= 4;
	// svgSprite->updateModel();

	while (!gui::Graphics::shouldClose())
	{
		// Update logic

		if (Input::keyboardStates[GLFW_KEY_ESCAPE])
			gui::Graphics::forceClose = true;

		// gui::Graphics::currentCamera->move({1, 0});
		// rect->sprite->texture->updateUBO();

		// Render to target
		gui::Graphics::setRenderTexture(renderTexture);
		gui::Graphics::clearScreen({0, 0, 0});
		rect->sprite->batch();
		rect->sprite->texture->draw();

		// Render to default "canvas"
		gui::Graphics::setRenderTexture();
		gui::Graphics::clearScreen({255, 143, 119});
		
		renderTexture->batch();
		renderTexture->texture->draw();

		// font->batch();
		// font->texture->draw();

		text->renderTexture->batch();
		text->renderTexture->texture->draw();

		// svgSprite->batch();
		// svgSprite->texture->draw();

		// rect->sprite->batch();
		// rect->sprite->texture->draw();

		gui::Graphics::endFrame();
	}

	delete font;
	delete rect;
	delete renderTexture;

	gui::Graphics::finalize();
	return 0;
}