#include "font.hpp"

using namespace gui;

Font::Font(const char *fontPath, unsigned int fontSize)
: Drawable::Drawable( new Texture{fontPath, fontSize, glyphs, 1} ), fontSize(fontSize)
{}

Font::~Font()
{
	delete glyphs;
	delete texture;
}
