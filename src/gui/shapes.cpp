#include "gui/shapes.hpp"

using namespace gui::shape;

Shape::Shape()
: texture(nullptr), sprite(nullptr)
{}

Rectangle::~Rectangle()
{
  if (sprite) sprite->~Sprite();
  if (texture) texture->~Texture();
}

void Rectangle::rebuild(unsigned int width, unsigned int height, unsigned int roundness, unsigned int thickness, std::string_view fill, std::string_view stroke)
{
  const std::string svg = std::format(
R"(<?xml version='1.0' encoding='UTF-8'?>
<svg
  width='{4:d}'
  height='{5:d}'>
  <g
    transform='translate({6:.2f},{6:.2f})'>
    <rect
      style='fill:#{7};fill-opacity:1;stroke:#{8};stroke-width:{2:d}'
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
thickness / 2.0f,   // 6
fill,               // 7
stroke              // 8
);

  if (texture)
  {
    unsigned char *pixelData;
    unsigned int newWidth, newHeight;
    Texture::getPixelDataSVGPercentRAW(svg, pixelData, 1.0f, &newWidth, &newHeight);
    texture->updateTexture(pixelData, newWidth, newHeight);
  }
  else
    texture = new (bufferTexture) Texture{svg, 1.0f, 1};

  if (sprite) sprite->~Sprite();
  sprite = new (bufferSprite) Sprite{texture};
}
