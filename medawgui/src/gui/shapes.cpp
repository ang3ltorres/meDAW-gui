#include "gui/shapes.hpp"

using namespace gui::shape;

Rectangle::Rectangle(unsigned int width, unsigned int height, unsigned int roundness, unsigned int thickness)
{
const std::string svgRectanleRounded = fmt::format(
R"(<?xml version='1.0' encoding='UTF-8' standalone='no'?>
<svg
  width='{4:d}'
  height='{5:d}'>
  <g
    transform='translate({6:.2f},{6:.2f})'>
    <rect
      style='fill:#ff0000;fill-opacity:1;stroke:#0000ff;stroke-width:{2:d}'
      width='{0:d}'
      height='{1:d}'
      x='0'
      y='0'
      ry='{3:d}'>
    </rect>
  </g>
</svg>)",
width,              // 0
height,             // 1
thickness,          // 2
roundness,          // 3
width + thickness,  // 4
height + thickness, // 5
thickness / 2.0f    // 6
);

	fmt::println(svgRectanleRounded);

	texture = new Texture(svgRectanleRounded, 1.0f, 1);
	sprite = new Sprite(texture);
}

Rectangle::~Rectangle()
{
	delete sprite;
	delete texture;
}

