#include "core/graphics.hpp"
#include "gui/editor.hpp"

using namespace gui;

int main()
{
	unsigned int width = 1280;
	unsigned int height = 720;

	
	Graphics::initialize(width, height, "OpenGL");
	
	RenderTexture *renderTexture = new RenderTexture{800, 600};

	Font *font = new Font{"../font/mononoki-Bold.ttf", 90};

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

	Text *text = new Text{font, "Hello world!!", 0.9f};

	// renderTexture->dst.z *= 1;
	// renderTexture->dst.w *= 1;
	// renderTexture->updateModel();

	// svgSprite->dst.z *= 4;
	// svgSprite->dst.w *= 4;
	// svgSprite->updateModel();

	// Render to default "canvas"
	// Force firts draw to avoid bugs on Wayland and epilepsy
	Graphics::setRenderTexture();
	Graphics::drawBuffer();
	Editor::initialize();

	while (!Graphics::shouldClose())
	{

		if (Event::keyboardStates[GLFW_KEY_ESCAPE])
			Graphics::forceClose = true;

		Graphics::pollEvents();
	}

	delete font;
	delete renderTexture;

	Editor::finalize();
	Graphics::finalize();
	return 0;
}