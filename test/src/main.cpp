#include "core/graphics.hpp"
#include "gui/editor.hpp"

using namespace gui;

int main()
{
	unsigned int width = 1280;
	unsigned int height = 720;

	
	Graphics::initialize(width, height, "OpenGL");
	Editor::initialize();
	
	RenderTexture *renderTexture = new RenderTexture{800, 600};

	Font *font = new Font{"../font/mononoki-Bold.ttf", 90};

	shape::Rectangle *rect = new shape::Rectangle(50, 150, 0, 0);

	// auto it = font->glyphs->find('p');
	// const Glyph &glyph = it->second;
	// font->src =
	// {
	// 	glyph.atlasPos.x,
	// 	glyph.atlasPos.y,
	// 	glyph.size.x,
	// 	glyph.size.y
	// };

	// font->dst =
	// {
	// 	128,
	// 	128,
	// 	glyph.size.x,
	// 	glyph.size.y
	// };

	// font->updateModel();

	Text *text = new Text{font, "Hello world!! que para", 0.9f};

	// renderTexture->dst.z *= 1;
	// renderTexture->dst.w *= 1;
	// renderTexture->updateModel();

	// svgSprite->dst.z *= 4;
	// svgSprite->dst.w *= 4;
	// svgSprite->updateModel();

	// Render to default "canvas"
	//Graphics::setRenderTexture();
	Graphics::clearScreen({255, 143, 119});
	glfwSwapBuffers(Graphics::window);
	Graphics::clearScreen({255, 143, 119});

	while (!Graphics::shouldClose())
	{
		// Update logic
		text->renderTexture->dst.y += 1.0f;
		text->renderTexture->updateModel();

		if (Event::keyboardStates[GLFW_KEY_ESCAPE])
			Graphics::forceClose = true;

		// Graphics::currentCamera->move({1, 0});
		// rect->sprite->texture->updateUBO();

		// Render to target
		Graphics::setRenderTexture(renderTexture);
		Graphics::clearScreen({255, 0, 255});

		text->renderTexture->batch();
		text->renderTexture->texture->draw();

		rect->sprite->batch();
		rect->sprite->texture->draw();

		// Render to default "canvas"
		Graphics::setRenderTexture();
		//Graphics::clearScreen({255, 143, 119});
		
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

		Graphics::endFrame();
	}

	delete font;
	delete rect;
	delete renderTexture;

	Editor::finalize();
	Graphics::finalize();
	return 0;
}