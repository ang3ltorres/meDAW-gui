#include "texture.hpp"

#include "graphics.hpp"

using namespace gui;

// *Generic Vertex data for drawing 2d stuff
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
}

void Texture::finalize()
{
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

	// Transform to RGBA format
	static unsigned char temp;
	for (unsigned int i = 0; i < bufferSize; i += 4)
	{
		// Swap bytes
		temp          = buffer[i];
		buffer[i]     = buffer[i + 2];
		buffer[i + 2] = temp;
	}
	
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

	// Transform to RGBA format
	unsigned char temp;
	for (unsigned int i = 0; i < bufferSize; i += 4)
	{
		// Swap bytes directly
		temp = buffer[i];
		buffer[i] = buffer[i + 2];
		buffer[i + 2] = temp;
	}
	
	plutovg_surface_destroy(surface);
	plutosvg_document_destroy(document);
}

Texture::Texture(const char *fileName, unsigned int maxInstances)
: maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataPNG(fileName, pixelData, &width, &height);

	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, 1, GL_RGBA8, width, height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	type = 0;
	glCreateBuffers(1, &UBO);
	glNamedBufferData(UBO, sizeof(int), &type, GL_STREAM_DRAW);

	glCreateBuffers(1, &SSBO);
	glNamedBufferData(SSBO, sizeof(S_Common) * maxInstances, nullptr, GL_STREAM_DRAW);
	SSBO_Data = new S_Common[maxInstances];
}

Texture::Texture(const char *fileName, unsigned int width, unsigned int height, unsigned int maxInstances)
: width(width), height(height), maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataSVGFixed(fileName, pixelData, width, height);

	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, 1, GL_RGBA8, width, height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	type = 0;
	glCreateBuffers(1, &UBO);
	glNamedBufferData(UBO, sizeof(int), &type, GL_STREAM_DRAW);

	glCreateBuffers(1, &SSBO);
	glNamedBufferData(SSBO, sizeof(S_Common) * maxInstances, nullptr, GL_STREAM_DRAW);
	SSBO_Data = new S_Common[maxInstances];
}

Texture::Texture(const char *fileName, float percent, unsigned int maxInstances)
: maxInstances(maxInstances), currentInstance(0)
{
	Texture::getPixelDataSVGPercent(fileName, pixelData, percent, &width, &height);

	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, 1, GL_RGBA8, width, height);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	type = 0;
	glCreateBuffers(1, &UBO);
	glNamedBufferData(UBO, sizeof(int), &type, GL_STREAM_DRAW);

	glCreateBuffers(1, &SSBO);
	glNamedBufferData(SSBO, sizeof(S_Common) * maxInstances, nullptr, GL_STREAM_DRAW);
	SSBO_Data = new S_Common[maxInstances];
}

Texture::Texture(unsigned int width, unsigned int height, unsigned int maxInstances)
: width(width), height(height), maxInstances(maxInstances), currentInstance(0)
{
	// *Create empty texture
	unsigned char color[4] = { 0, 0, 0, 255 };
	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, 1, GL_RGBA8, width, height);
	glClearTexSubImage(id, 0, 0, 0, 0, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	type = 1;
	glCreateBuffers(1, &UBO);
	glNamedBufferData(UBO, sizeof(int), &type, GL_STREAM_DRAW);

	glCreateBuffers(1, &SSBO);
	glNamedBufferData(SSBO, sizeof(S_Common) * maxInstances, nullptr, GL_STREAM_DRAW);
	SSBO_Data = new S_Common[maxInstances];

	pixelData = nullptr;
}

Texture::~Texture()
{
	glDeleteBuffers(1, &UBO);
	glDeleteBuffers(1, &SSBO);
	glDeleteTextures(1, &id);
	SSBO_Data = new S_Common[maxInstances];
	delete[] SSBO_Data;
	delete[] pixelData;
}

void Texture::draw()
{
	Texture::shader->use();
	Graphics::setVAO(Texture::VAO);
	Graphics::setTexture(id);
	
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO);
	// glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(int), &type);
	
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(S_Common) * currentInstance, SSBO_Data);
	
	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, currentInstance);
	currentInstance = 0;
}


