#include "widget/button.hpp"

using namespace gui::widget;
using namespace gui::shape;


Button::Button(glm::ivec2 pos, glm::uvec2 size, unsigned char type, std::function<void()> function)
: Widget(pos, size), function(function), type(type)
{
	rect = new Rectangle{size.x, size.y, 8, 4};
	rect->sprite->dst = {pos.x, pos.y, size.x, size.y};

	texture.push_back(rect->texture);
}

Button::~Button()
{
	delete rect;
}

void Button::draw()
{
	rect->sprite->batch();
	rect->sprite->texture->draw();
}