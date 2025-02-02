#pragma once

#include "pch.hpp"

#include "shader.hpp"
#include "renderTexture.hpp"
#include "font.hpp"

namespace gui
{
	class Text
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

		Text(gui::Font *font, const char *text);
		Text(const Text &) = delete;
		~Text();

		static Shader *shader;
		static GLuint VAO;
		static GLuint VBO;
		static GLuint EBO;
		static GLuint UBO_Shared;
		static GPU_UBO UBO_Data;

		static void initialize();
		static void finalize();

		gui::Font *font;
		gui::RenderTexture *renderTexture;

		void render(const char *text);
	};
}

