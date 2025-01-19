#pragma once

#include "pch.hpp"

#include "color.hpp"
#include "texture.hpp"

namespace gui
{
	class Drawable
	{
	public:
		Drawable(const Drawable&) = delete;
		Drawable(Texture *texture);
		~Drawable() = default;

		Texture *texture;
		
		glm::ivec4 src;
		glm::ivec4 dst;
		Color color;
		float rotation;

		void updateModel();
		void batch();

		glm::mat4 model;
	};
}
