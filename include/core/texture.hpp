#pragma once

#include "pch.hpp"

#include "core/shader.hpp"
#include "core/glyph.hpp"

namespace gui
{
	class Texture
	{
	public:

		struct alignas(16) GPU_SSBO
		{
			glm::vec4 Src;
			glm::vec4 TintColor;
			glm::mat4 Model;
		};

		struct alignas(16) GPU_UBO
		{
			alignas(16) glm::mat4 ViewProjection;
		};

		GLuint id;
		GLuint width;
		GLuint height;

		static void initialize();
		static void finalize();

		static void getPixelDataPNG(const char *fileName, unsigned char *&buffer, unsigned int *width, unsigned int *height);
		static void getPixelDataSVGFixed(const char *fileName, unsigned char *&buffer, unsigned int widthDesired, unsigned int heightDesired);
		static void getPixelDataSVGFixedRAW(const std::string &svgData, unsigned char *&buffer, unsigned int widthDesired, unsigned int heightDesired);
		static void getPixelDataSVGPercent(const char *fileName, unsigned char *&buffer, float percent, unsigned int *width, unsigned int *height);
		static void getPixelDataSVGPercentRAW(const std::string &svgData, unsigned char *&buffer, float percent, unsigned int *width, unsigned int *height);
		static void getPixelDataFont(const char *fontPath, unsigned int fontSize, Glyph *glyphs, unsigned char *&buffer, unsigned int *width, unsigned int *height);

		//* Generic Draw Texture 2D stuff
		static Shader *shader;
		static GLuint VAO;
		static GLuint VBO;
		static GLuint EBO;
		static GLuint UBO_Shared;
		static GPU_UBO UBO_Data;
		
		// Constructor common
		void createTexture(unsigned char *pixelData);
		void createBuffers(int textureType);

		Texture(const char *fileName, unsigned int maxInstances);
		Texture(const char *fileName, unsigned int width, unsigned int height, unsigned int maxInstances);
		Texture(const std::string &svgData, unsigned int width, unsigned int height, unsigned int maxInstances);
		Texture(const char *fileName, float percent, unsigned int maxInstances);
		Texture(const std::string &svgData, float percent, unsigned int maxInstances);
		Texture(const char *fontPath, unsigned int fontSize, Glyph *glyphs, unsigned int maxInstances);
		Texture(unsigned int width, unsigned int height, unsigned int maxInstances);
		Texture(const Texture&) = delete;
		~Texture();

		void updateTexture(unsigned char *pixelData, unsigned int newWidth, unsigned int newHeight);

		GLuint UBO_NonShared;
		int Type;

		GLuint SSBO;
		GPU_SSBO *SSBO_Data;
		unsigned int maxInstances;
		unsigned int currentInstance;

		void draw();
	};
}
