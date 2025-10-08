#pragma once

#include "pch.hpp"

#include "core/color.hpp"
#include "core/input.hpp"
#include "core/shader.hpp"
#include "core/camera.hpp"
#include "core/texture.hpp"
#include "core/sprite.hpp"
#include "core/renderTexture.hpp"
#include "core/text.hpp"

#include "gui/shapes.hpp"
#include "gui/palette.hpp"

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
	};
}