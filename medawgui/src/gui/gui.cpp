#include "gui/gui.hpp"

using namespace gui;
using namespace glm;

Widget::Widget(ivec2 pos, uvec2 size)
: pos(pos), size(size), texture()
{

}

Pane::Pane(const glm::ivec2& pos, const glm::uvec2& size, const std::string& name)
: pos(pos), size(size), name(name), widget()
{

}