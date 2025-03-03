#include "text.hpp"

#include "graphics.hpp"

using namespace gui;

Text::Text(Font *font, const char *text, float gap)
: font(font), renderTexture(nullptr), gap(gap)
{
	render(text);
}

void Text::render(const char *text)
{
	// Precalculate required texture size
	float width = 0.0f;
	float maxHeight = 0.0f;
	float minY = 0.0f;

	float scale = 1.0f;

	for (const char *c = text; *c; c++)
	{
		if (*c == ' ') {

			width += font->fontSize * 0.25f;
			continue;
		}

		auto it = font->glyphs->find(*c);
		if (it == font->glyphs->end())
			continue;

		const gui::Glyph &glyph = it->second;

		width += glyph.advance * scale;

		// Calculate the max height considering the top and bottom bearings
		float glyphTop = glyph.bearing.y;
		float glyphBottom = glyph.bearing.y - glyph.size.y;

		// Update max height for the tallest glyphs
		maxHeight = std::max(maxHeight, glyphTop * scale);
		// Update minY for the lowest point (descender)
		minY = std::min(minY, glyphBottom * scale);
	}

	unsigned int textureWidth  = (unsigned int)std::ceil(width);
	unsigned int textureHeight = (unsigned int)std::ceil(maxHeight - minY);

	textureWidth  = std::max(textureWidth, 1u); // Ensure non-zero size
	textureHeight = std::max(textureHeight, 1u);

	// Create or update the RenderTexture
	delete renderTexture;
	renderTexture = new gui::RenderTexture{textureWidth, textureHeight};

	// Bind the RenderTexture to draw text into it
	Graphics::setRenderTexture(renderTexture);

	float x = 0.0f;

	for (const char *c = text; *c; c++)
	{
		if (*c == ' ')
		{
			x += font->fontSize * 0.25f; //  Space character advance
			continue;
		}

		auto it = font->glyphs->find(*c);
		if (it == font->glyphs->end())
			continue;

		const gui::Glyph &glyph = it->second;

		// Setup texture coordinates (UVs from the atlas)
		font->src =
		{
			glyph.atlasPos.x,
			glyph.atlasPos.y,
			glyph.size.x,
			glyph.size.y
		};

		// Position the glyph within the render texture
		font->dst =
		{
			x + glyph.bearing.x,                   // X position with horizontal bearing
			maxHeight - glyph.bearing.y,           // Y position adjusted for vertical bearing
			glyph.size.x,                          // Width of the glyph
			glyph.size.y                           // Height of the glyph
		};

		// Update model matrix and batch the glyph for rendering
		font->updateModel();
		font->batch();

		// Advance the cursor for the next glyph
		x += glyph.advance * scale * gap;
	}

	// Draw all batched glyphs
	font->texture->draw();

	// Reset font texture coordinates for the full texture
	// font->src = {0, 0, font->texture->width, font->texture->height};
	// font->dst = {0, 0, font->texture->width, font->texture->height};
	// font->updateModel();

	// Step 4: Unbind the FBO
	Graphics::setRenderTexture();
}
