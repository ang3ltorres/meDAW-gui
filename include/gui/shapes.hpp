#pragma once

#include "core/graphics.hpp"

namespace gui::shape
{
	class Shape
	{
	public:
		Shape();
		Shape(const Shape&) = delete;
		virtual ~Shape() = default;

		alignas(Texture) unsigned char bufferTexture[sizeof(Texture)];
		Texture *texture;
		
		alignas(Sprite) unsigned char bufferSprite[sizeof(Sprite)];
		Sprite *sprite;
	};

	class Rectangle : public Shape
	{
	public:
		Rectangle() = default;
		Rectangle(const Rectangle&) = delete;
		virtual ~Rectangle() override;

		void rebuild(unsigned int width, unsigned int height, unsigned int roundness, unsigned int thickness, std::string_view fill, std::string_view stroke);
	};
}