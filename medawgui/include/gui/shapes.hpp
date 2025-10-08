#pragma once

#include "core/graphics.hpp"

namespace gui::shape
{
	class Shape
	{
	public:
		Shape() = default;
		Shape(const Shape&) = delete;
		~Shape() = default;

		gui::Texture *texture;
		gui::Sprite  *sprite;
	};

	class Rectangle : public Shape
	{
	public:
		Rectangle(unsigned int width, unsigned int height, unsigned int roundness, unsigned int thickness);
		Rectangle(const Rectangle&) = delete;
		~Rectangle();
	};
}