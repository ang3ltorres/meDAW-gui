#pragma once

#include "pch.hpp"

#include "color.hpp"
#include "input.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include "sprite.hpp"
#include "renderTexture.hpp"

#include "gui/shapes.hpp"

namespace gui
{
	class Graphics
	{
	public:
		Graphics() = delete;
		Graphics(const Graphics&) = delete;
		~Graphics() = default;

		static void initialize(int width, int height, const char *title);
		static void finalize();
		
		static void begin();

		// Window
		static GLFWwindow *window;
		static unsigned int width;
		static unsigned int height;
		static bool forceClose;

		// Input
		static Input *input;

		// Default stuff
		static GLuint currentVAO;
		static GLuint currentTexture;
		static Camera *currentCamera;
		static Camera *defaultCamera;

		// Time Travel stuff
		static float fps;
		static float delta;

		// Library Methods
		static bool shouldClose();
		static void clearScreen(const Color &color);
		static void setRenderTexture(RenderTexture *renderTexture = nullptr);
		static void setVAO(GLuint VAO);
		static void setTexture(GLuint texture);
		static void endFrame();
		static void setResizeCallback(GLFWframebuffersizefun callback);
	};
}