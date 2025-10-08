#include "gui/gui.hpp"

using namespace gui;
using namespace glm;

Widget::Widget(const glm::ivec2& pos, const glm::uvec2& size, const std::string& name)
: pos(pos), size(size), name(name), shapes()
{}

