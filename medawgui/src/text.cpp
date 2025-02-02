#include "text.hpp"

#include "graphics.hpp"

using namespace gui;

Shader *Text::shader;

static const unsigned int indices[] =
{
	0, 1, 2,
	1, 2, 3,
};

void Text::initialize()
{
	// Load text rendering shader
	Text::shader = new Shader("../shader/text.vs", "../shader/text.fs");

	// Create VAO for text rendering
	glCreateVertexArrays(1, &Text::VAO);

	// Create VBO for dynamic text rendering
	glCreateBuffers(1, &Text::VBO);
	glNamedBufferStorage(Text::VBO, 1024 * sizeof(float), nullptr, GL_DYNAMIC_STORAGE_BIT); // Allocated but empty

	// Create EBO for indexed rendering
	glCreateBuffers(1, &Text::EBO);
	glNamedBufferStorage(Text::EBO, sizeof(indices), indices, 0);

	// Link buffers
	glVertexArrayElementBuffer(Text::VAO, Text::EBO);

	GLuint vbufIndex = 0;
	glVertexArrayVertexBuffer(Text::VAO, vbufIndex, Text::VBO, 0, sizeof(float) * 4);

	// Position attribute (layout(location = 0) in vec2 aPos)
	GLuint aPos_location = 0;
	glVertexArrayAttribFormat(Text::VAO, aPos_location, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(Text::VAO, aPos_location, vbufIndex);
	glEnableVertexArrayAttrib(Text::VAO, aPos_location);

	// Texture coordinate attribute (layout(location = 1) in vec2 aTexCoord)
	GLuint aTexCoord_location = 1;
	glVertexArrayAttribFormat(Text::VAO, aTexCoord_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2);
	glVertexArrayAttribBinding(Text::VAO, aTexCoord_location, vbufIndex);
	glEnableVertexArrayAttrib(Text::VAO, aTexCoord_location);

	// Create shared UBO for view-projection matrix
	glCreateBuffers(1, &Text::UBO_Shared);
	glNamedBufferData(Text::UBO_Shared, sizeof(Text::GPU_UBO), nullptr, GL_STREAM_DRAW);

	//! Fill camera buffer (UBO_Shared)
	glCreateBuffers(1, &Texture::UBO_Shared);
	glNamedBufferData(Texture::UBO_Shared, sizeof(Texture::GPU_UBO), nullptr, GL_STREAM_DRAW);
}

void Text::finalize()
{
	delete Texture::shader;
}

Text::Text(Font *font, const char *text)
: font(font)
{
	render(text);
}

void Text::render(const char *text)
{
	// Step 1: Calculate required texture size
	float width = 0.0f;
	float maxHeight = 0.0f;
	float scale = 1.0f;

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

	unsigned int textureWidth = static_cast<unsigned int>(std::ceil(width));
	unsigned int textureHeight = static_cast<unsigned int>(std::ceil(maxHeight));

	textureWidth = std::max(textureWidth, 1u);
	textureHeight = std::max(textureHeight, 1u);

	// Step 2: Create RenderTexture
	renderTexture = new gui::RenderTexture{textureWidth, textureHeight};

	// Step 4: Bind FBO and render text into the texture
	Graphics::setRenderTexture(renderTexture);

	float x = 0.0f, y = 0.0f;
	std::vector<float> vertices;

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

		float xpos = x + glyph.bearing.x * scale;
		float ypos = y - (glyph.bearing.y - glyph.size.y) * scale;
		float w = glyph.size.x * scale;
		float h = glyph.size.y * scale;

		float uMin = glyph.uvMin.x;
		float vMin = glyph.uvMin.y;
		float uMax = glyph.uvMax.x;
		float vMax = glyph.uvMax.y;

		vertices.insert(vertices.end(),
		{
			xpos,     ypos + h, uMin, vMax, 
			xpos,     ypos,     uMin, vMin, 
			xpos + w, ypos,     uMax, vMin, 

			xpos,     ypos + h, uMin, vMax, 
			xpos + w, ypos,     uMax, vMin, 
			xpos + w, ypos + h, uMax, vMax  
		});

		x += glyph.advance * scale;
	}

	Text::shader->use();
	Graphics::setVAO(Text::VAO);
	Graphics::setTexture(renderTexture->texture->id);

	// Upload vertex data

	// using modern opengl

	// Step 5: Unbind FBO (Back to screen rendering)
	Graphics::setRenderTexture(0);
}

