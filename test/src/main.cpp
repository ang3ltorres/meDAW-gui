#include "graphics.hpp"

static void resized([[maybe_unused]] GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	gui::Graphics::defaultCamera->width  = width;
	gui::Graphics::defaultCamera->height = height;

	gui::Graphics::width  = width;
	gui::Graphics::height = height;
}

int main()
{
	unsigned int width = 1280;
	unsigned int height = 720;
	
	gui::Graphics::initialize(width, height, "OpenGL");
	gui::Graphics::setResizeCallback(&resized);
	
	gui::RenderTexture *renderTexture = new gui::RenderTexture{800, 600};
	gui::Texture       *svgTexture    = new gui::Texture{"../test/test.svg", 256, 256, 1};
	gui::Sprite        *svgSprite     = new gui::Sprite{svgTexture};

	renderTexture->dst.z *= 1;
	renderTexture->dst.w *= 1;
	renderTexture->updateModel();

	while (!gui::Graphics::shouldClose())
	{
		// Update logic
		svgSprite->dst.x += 1;
		svgSprite->updateModel();

		// Render to target
		gui::Graphics::setRenderTexture(renderTexture);
		gui::Graphics::clearScreen({0, 255, 0});

		// Render to default "canvas"
		gui::Graphics::setRenderTexture();
		gui::Graphics::clearScreen({255, 143, 119});
		renderTexture->batch();
		renderTexture->texture->draw();

		svgSprite->batch();
		svgSprite->texture->draw();

		gui::Graphics::endFrame();
	}

	delete svgTexture;
	delete renderTexture;

	gui::Graphics::finalize();
	return 0;
}