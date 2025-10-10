#pragma once

#include "pch.hpp"

#include "core/drawable.hpp"
#include "core/camera.hpp"

namespace gui
{
	class RenderTexture : public Drawable
	{
	public:
		RenderTexture(unsigned int width, unsigned int height, Camera *camera = nullptr);
		RenderTexture(const RenderTexture&) = delete;
		~RenderTexture();

		GLuint FBO;

		bool internalCamera;
		Camera *camera;
	};
}
