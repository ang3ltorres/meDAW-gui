#include "text.hpp"

#include "graphics.hpp"

using namespace gui;

Text::Text(Font *font, const char *text)
: font(font), renderTexture(nullptr)
{
	render(text);
}

void Text::render(const char *text)
{
	// Step 1: Calculate required texture size
	float width     = 0.0f;
	float maxHeight = 0.0f;
	float scale     = 1.0f;

	for (const char *c = text; *c; c++)
	{
		if (*c == ' ')
		{
			width += font->fontSize * 0.25f;
			continue;
		}

		auto it = font->glyphs->find(*c);
		if (it == font->glyphs->end())
			continue;

		const gui::Glyph &glyph = it->second;

		width += glyph.advance * scale;
		maxHeight = std::max(maxHeight, glyph.size.y * scale);
	}

	unsigned int textureWidth  = (unsigned int)std::ceil(width);
	unsigned int textureHeight = (unsigned int)std::ceil(maxHeight);

	textureWidth  = std::max(textureWidth, 1u);
	textureHeight = std::max(textureHeight, 1u);

	// Step 2: Create or update the RenderTexture
	delete renderTexture;
	renderTexture = new gui::RenderTexture{textureWidth, textureHeight};

	// Step 3: Bind the FBO and to draw text
	Graphics::setRenderTexture(renderTexture);

	float x = 0.0f;
	float y = 0.0f;

	for (const char *c = text; *c; c++)
	{
		if (*c == ' ') 
		{
			x += font->fontSize * 0.25f;
			continue;
		}

		auto it = font->glyphs->find(*c);
		if (it == font->glyphs->end())
			continue;

		const gui::Glyph &glyph = it->second;

		// Setup texture coordinates (Atlas UVs)
		font->src = {glyph.atlasPos.x, glyph.atlasPos.y, glyph.size.x, glyph.size.y};

		// Position the glyph
		font->dst = {x + glyph.bearing.x * scale, y - (glyph.bearing.y - glyph.size.y) * scale, glyph.size.x * scale, glyph.size.y * scale};

		// Update model matrix & batch
		font->updateModel();
		font->batch();

		// Move to the next glyph position
		x += glyph.advance * scale;
	}

	// Draw all batched glyphs
	font->texture->draw();

	font->src = {0, 0, font->texture->width, font->texture->height};
	font->dst = {0, 0, font->texture->width, font->texture->height};
	font->updateModel();

	// Step 4: Unbind FBO
	Graphics::setRenderTexture();
}

