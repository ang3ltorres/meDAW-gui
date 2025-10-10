#pragma once

#include "pch.hpp"

#include "core/color.hpp"
#include "core/texture.hpp"

namespace gui
{
	class Drawable
	{
	public:
		Drawable(Texture *texture);
		Drawable(const Drawable&) = delete;
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
