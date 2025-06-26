#include "gui/gui.hpp"

using namespace gui;
using namespace glm;

std::vector<Pane> pane = {};

Widget::Widget(ivec2 pos, uvec2 size)
: pos(pos), size(size), texture()
{

}