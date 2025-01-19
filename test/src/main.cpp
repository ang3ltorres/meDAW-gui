#include "graphics.hpp"

int main()
{
	unsigned int width = 800;
	unsigned int height = 600;
	
	gui::Graphics::initialize(width, height, "OpenGL");
	
	gui::RenderTexture *renderTexture = new gui::RenderTexture{256, 240};
	gui::Texture       *pngTexture    = new gui::Texture{"D:/sglf_res/png_test.png", 1};
	gui::Sprite        *pngSprite     = new gui::Sprite{pngTexture, {0, 0, 400, 300}, {0, 0, 400, 300}};
	// gui::Texture       *svgTexture    = new gui::Texture{"D:/sglf_res/Ghostscript_Tiger.svg", 256, 256, 1};
	gui::Texture       *svgTexture    = new gui::Texture{"D:/sglf_res/Ghostscript_Tiger.svg", 2.0f, 1};
	gui::Sprite        *svgSprite     = new gui::Sprite{svgTexture};

	renderTexture->dst.z *= 1;
	renderTexture->dst.w *= 1;
	renderTexture->updateModel();

	svgSprite->dst.x -= 200;
	svgSprite->dst.y -= 200;
	svgSprite->updateModel();

	while (!gui::Graphics::shouldClose())
	{
		// Update logic

		// Render to target
		gui::Graphics::setRenderTexture(renderTexture);
		gui::Graphics::clearScreen({255, 255, 255});

		pngSprite->batch();
		pngSprite->texture->draw();

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
	delete pngSprite;
	delete pngTexture;
	delete renderTexture;

	gui::Graphics::finalize();
	return 0;
}