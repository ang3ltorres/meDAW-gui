#include "texture.hpp"

#include "graphics.hpp"

using namespace gui;

//* Generic Vertex data for drawing 2d stuff
struct Vertex
{
	GLfloat position[2];
	GLfloat uv[2];
};

static const Vertex vertices[] =
{
	{ { 0.0f, 0.0f }, { 0.0f, 0.0f } },
	{ { 1.0f, 0.0f }, { 1.0f, 0.0f } },
	{ { 0.0f, 1.0f }, { 0.0f, 1.0f } },
	{ { 1.0f, 1.0f }, { 1.0f, 1.0f } }
};

static const unsigned int indices[] =
{
	0, 1, 2,
	1, 2, 3,
};

Shader *Texture::shader;
GLuint Texture::VAO;
GLuint Texture::VBO;
GLuint Texture::EBO;
GLuint Texture::UBO_Shared;
Texture::GPU_UBO Texture::UBO_Data;

static void ARGBtoRGBA(unsigned char *&buffer, unsigned int size)
{
	for (unsigned int i = 0; i < size; i += 4)
	{
		buffer[i]     ^= buffer[i + 2];
		buffer[i + 2] ^= buffer[i];
		buffer[i]     ^= buffer[i + 2];
	}
}

void Texture::initialize()
{
	//* VAO/Shader For 2D Texture drawing
	Texture::shader = new Shader("../shader/texture.vs", "../shader/texture.fs");

	glCreateVertexArrays(1, &Texture::VAO);

	glCreateBuffers(1, &Texture::VBO);
	glNamedBufferStorage(Texture::VBO, sizeof(vertices), vertices, 0);

	glCreateBuffers(1, &Texture::EBO);
	glNamedBufferStorage(Texture::EBO, sizeof(indices), indices, 0);

	glVertexArrayElementBuffer(Texture::VAO, Texture::EBO);

	GLuint vbufIndex = 0;
	glVertexArrayVertexBuffer(Texture::VAO, vbufIndex, Texture::VBO, 0, sizeof(Vertex));

	//! layout(location = 0) in vec2 aPos;
	GLuint aPos_location = 0;
	glVertexArrayAttribFormat(Texture::VAO, aPos_location, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	glVertexArrayAttribBinding(Texture::VAO, aPos_location, vbufIndex);
	glEnableVertexArrayAttrib(Texture::VAO, aPos_location);

	//! layout(location = 1) in vec2 aTexCoord;
	GLuint aTexCoord_location = 1;
	glVertexArrayAttribFormat(Texture::VAO, aTexCoord_location, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));
	glVertexArrayAttribBinding(Texture::VAO, aTexCoord_location, vbufIndex);
	glEnableVertexArrayAttrib(Texture::VAO, aTexCoord_location);

	//! Fill camera buffer (UBO_Shared)
	Texture::UBO_Data.ViewProjection = Graphics::currentCamera->viewProjection;
	glCreateBuffers(1, &Texture::UBO_Shared);
	glNamedBufferData(Texture::UBO_Shared, sizeof(Texture::GPU_UBO), &Texture::UBO_Data, GL_STREAM_DRAW);
}

void Texture::finalize()
{
	glDeleteBuffers(1, &Texture::UBO_Shared);
	glDeleteBuffers(1, &Texture::EBO);
	glDeleteBuffers(1, &Texture::VBO);
	glDeleteVertexArrays(1, &Texture::VAO);
	delete Texture::shader;
}

void Texture::getPixelDataPNG(const char *fileName, unsigned char *&buffer, unsigned int *width, unsigned int *height)
{
	FILE *fp = fopen(fileName, "rb");

	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	png_infop info = png_create_info_struct(png);

	png_init_io(png, fp);
	png_read_info(png, info);

	*width  = png_get_image_width(png, info);
	*height = png_get_image_height(png, info);

	if (png_get_bit_depth(png, info) == 16)
		png_set_strip_16(png);

	if (png_get_color_type(png, info) == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);

	if (png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);

	if (png_get_color_type(png, info) == PNG_COLOR_TYPE_GRAY || 
		png_get_color_type(png, info) == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);

	png_read_update_info(png, info);

	size_t row_bytes = png_get_rowbytes(png, info);

	buffer = new unsigned char[row_bytes * (*height)];

	png_bytep *row_pointers = new png_bytep[*height];
	for (unsigned int y = 0; y < *height; y++)
		row_pointers[y] = buffer + y * row_bytes;

	png_read_image(png, row_pointers);

	delete[] row_pointers;
	png_destroy_read_struct(&png, &info, nullptr);
	fclose(fp);
}

void Texture::getPixelDataSVGFixed(const char *fileName, unsigned char *&buffer, unsigned int widthDesired, unsigned int heightDesired)
{
	plutosvg_document_t *document = plutosvg_document_load_from_file(fileName, -1, -1);
	
	// Get data in ARGB format
	plutovg_surface_t *surface = plutosvg_document_render_to_surface(document, nullptr, widthDesired, heightDesired, nullptr, nullptr, nullptr);

	unsigned int bufferSize = widthDesired * heightDesired * 4;
	unsigned char *data = plutovg_surface_get_data(surface);
	buffer = new unsigned char[bufferSize];
	memcpy(buffer, data, bufferSize);

	ARGBtoRGBA(buffer, bufferSize);
	
	plutovg_surface_destroy(surface);
	plutosvg_document_destroy(document);
}

void Texture::getPixelDataSVGFixedRAW(const std::string &svgData, unsigned char *&buffer, unsigned int widthDesired, unsigned int heightDesired)
{
	plutosvg_document_t *document = plutosvg_document_load_from_data(svgData.data(), svgData.length(), -1, -1, nullptr, nullptr);
	
	// Get data in ARGB format
	plutovg_surface_t *surface = plutosvg_document_render_to_surface(document, nullptr, widthDesired, heightDesired, nullptr, nullptr, nullptr);

	unsigned int bufferSize = widthDesired * heightDesired * 4;
	unsigned char *data = plutovg_surface_get_data(surface);
	buffer = new unsigned char[bufferSize];
	memcpy(buffer, data, bufferSize);

	ARGBtoRGBA(buffer, bufferSize);
	
	plutovg_surface_destroy(surface);
	plutosvg_document_destroy(document);
}

void Texture::getPixelDataSVGPercent(const char *fileName, unsigned char *&buffer, float percent, unsigned int *width, unsigned int *height)
{
	plutosvg_document_t *document = plutosvg_document_load_from_file(fileName, -1, -1);

	static plutovg_rect_t extents;
	plutosvg_document_extents(document, nullptr, &extents);

	*width  = extents.w * percent;
	*height = extents.h * percent;

	// Get data in ARGB format
	plutovg_surface_t *surface = plutosvg_document_render_to_surface(document, nullptr, *width, *height, nullptr, nullptr, nullptr);

	unsigned int bufferSize = (*width) * (*height) * 4;
	unsigned char *data = plutovg_surface_get_data(surface);
	buffer = new unsigned char[bufferSize];
	memcpy(buffer, data, bufferSize);

	ARGBtoRGBA(buffer, bufferSize);
	
	plutovg_surface_destroy(surface);
	plutosvg_document_destroy(document);
}

void Texture::getPixelDataSVGPercentRAW(const std::string &svgData, unsigned char *&buffer, float percent, unsigned int *width, unsigned int *height)
{
	plutosvg_document_t *document = plutosvg_document_load_from_data(svgData.data(), svgData.length(), -1, -1, nullptr, nullptr);

	static plutovg_rect_t extents;
	plutosvg_document_extents(document, nullptr, &extents);

	*width  = extents.w * percent;
	*height = extents.h * percent;

	// Get data in ARGB format
	plutovg_surface_t *surface = plutosvg_document_render_to_surface(document, nullptr, *width, *height, nullptr, nullptr, nullptr);

	unsigned int bufferSize = (*width) * (*height) * 4;
	unsigned char *data = plutovg_surface_get_data(surface);
	buffer = new unsigned char[bufferSize];
	memcpy(buffer, data, bufferSize);

	ARGBtoRGBA(buffer, bufferSize);
	
	plutovg_surface_destroy(surface);
	plutosvg_document_destroy(document);
}

void Texture::getPixelDataFont(const char *fontPath, unsigned int fontSize, std::map<char, gui::Glyph> *&glyphs, unsigned char *&buffer, unsigned int *width, unsigned int *height)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		fmt::println("Could not initialize FreeType library");
		return;
	}

	FT_Face face;
	if (FT_New_Face(ft, fontPath, 0, &face))
	{
		fmt::println("Failed to load font {}", fontPath);
		return;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	// 1. Determine total area required for all glyphs and max dimensions
	unsigned int totalArea = 0;
	unsigned int maxGlyphWidth = 0, maxGlyphHeight = 0;

	for (unsigned int c = 32; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			fmt::println("Failed to load glyph: {:c}", c);
			continue;
		}

		FT_Bitmap &bitmap = face->glyph->bitmap;
		if (bitmap.width == 0 || bitmap.rows == 0) continue; // Skip empty glyphs

		totalArea += bitmap.width * bitmap.rows;

		maxGlyphWidth = std::max(maxGlyphWidth, bitmap.width);
		maxGlyphHeight = std::max(maxGlyphHeight, bitmap.rows);
	}

	// 2. Estimate optimal texture size
	unsigned int estimatedSize = std::ceil(std::sqrt(totalArea)) * 1.2f; // Add extra 20% padding
	estimatedSize = std::max(estimatedSize, std::max(maxGlyphWidth, maxGlyphHeight)); // Ensure it fits at least one glyph

	// Round up to the nearest power of 2
	*width = *height = 1;
	while (*width < estimatedSize) *width *= 2;
	while (*height < estimatedSize) *height *= 2;

	buffer = new unsigned char[(*width) * (*height) * 4];
	memset(buffer, 0, (*width) * (*height) * 4);

	// 3. Pack Glyphs Using Shelf Packing Algorithm
	unsigned int xOffset = 0, yOffset = 0, currentRowHeight = 0;
	glyphs = new std::map<char, Glyph>{};

	for (unsigned int c = 32; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			continue;

		FT_Bitmap &bitmap = face->glyph->bitmap;
		if (bitmap.width == 0 || bitmap.rows == 0) continue;

		// If the glyph doesn't fit in the current row, move to the next row
		if (xOffset + bitmap.width > *width)
		{
			xOffset = 0;
			yOffset += currentRowHeight;
			currentRowHeight = 0;
		}

		if (yOffset + bitmap.rows > *height)
		{
			fmt::println("Warning: Texture size underestimated; some glyphs may not fit.");
			break; // If we exceed the buffer, we stop adding glyphs
		}

		// Copy glyph bitmap to atlas buffer
		for (unsigned int y = 0; y < bitmap.rows; y++)
		{
			for (unsigned int x = 0; x < bitmap.width; x++)
			{
				unsigned int bufferIndex = ((yOffset + y) * (*width) + (xOffset + x)) * 4;
				unsigned char alpha = bitmap.buffer[y * bitmap.pitch + x];

				buffer[bufferIndex + 0] = 255;   // R
				buffer[bufferIndex + 1] = 255;   // G
				buffer[bufferIndex + 2] = 255;   // B
				buffer[bufferIndex + 3] = alpha; // A
			}
		}

		// Store glyph metadata
		(*glyphs)[c] =
		{
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),  // Bearing
			glm::vec2(bitmap.width, bitmap.rows),                          // Size
			glm::ivec2(xOffset, yOffset),                                  // NEW: Absolute atlas position
			float(face->glyph->advance.x >> 6)                             // Advance
		};

		// Move to next position
		xOffset += bitmap.width;
		currentRowHeight = std::max(currentRowHeight, bitmap.rows);
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void Texture::createTexture()
{
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, 1, GL_RGBA8, width, height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::createBuffers(int textureType)
{
	glCreateBuffers(1, &SSBO);
	glNamedBufferData(SSBO, sizeof(GPU_SSBO) * maxInstances, nullptr, GL_STREAM_DRAW);
	SSBO_Data = new GPU_SSBO[maxInstances];

	Type = textureType;
	glCreateBuffers(1, &UBO_NonShared);
	glNamedBufferData(UBO_NonShared, sizeof(int), &Type, GL_STREAM_DRAW);
}

Texture::Texture(const char *fileName, unsigned int maxInstances)
: maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataPNG(fileName, pixelData, &width, &height);
	createTexture();
	createBuffers(0);
}

Texture::Texture(const char *fileName, unsigned int width, unsigned int height, unsigned int maxInstances)
: width(width), height(height), maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataSVGFixed(fileName, pixelData, width, height);
	createTexture();
	createBuffers(0);
}

Texture::Texture(const std::string &svgData, unsigned int width, unsigned int height, unsigned int maxInstances)
: width(width), height(height), maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataSVGFixedRAW(svgData, pixelData, width, height);
	createTexture();
	createBuffers(0);
}

Texture::Texture(const char *fileName, float percent, unsigned int maxInstances)
: maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataSVGPercent(fileName, pixelData, percent, &width, &height);
	createTexture();
	createBuffers(0);
}

Texture::Texture(const std::string &svgData, float percent, unsigned int maxInstances)
: maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataSVGPercentRAW(svgData, pixelData, percent, &width, &height);
	createTexture();
	createBuffers(0);
}

Texture::Texture(const char *fontPath, unsigned int fontSize, std::map<char, gui::Glyph> *& glyphs, unsigned int maxInstances)
: maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataFont(fontPath, fontSize, glyphs, pixelData, &width, &height);
	createTexture();
	createBuffers(0);
}

Texture::Texture(unsigned int width, unsigned int height, unsigned int maxInstances)
: width(width), height(height), maxInstances(maxInstances), currentInstance(0)
{
	pixelData = nullptr;
	createTexture();
	createBuffers(1);	
}

Texture::~Texture()
{
	glDeleteBuffers(1, &UBO_NonShared);
	glDeleteBuffers(1, &SSBO);
	glDeleteTextures(1, &id);
	SSBO_Data = new GPU_SSBO[maxInstances];
	delete[] SSBO_Data;
	delete[] pixelData;
}

void Texture::draw()
{
	Texture::shader->use();
	Graphics::setVAO(Texture::VAO);
	Graphics::setTexture(id);
	
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(GPU_SSBO) * currentInstance, SSBO_Data);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, Texture::UBO_Shared);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, Texture::UBO_NonShared);
	
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, currentInstance);
	currentInstance = 0;
}
