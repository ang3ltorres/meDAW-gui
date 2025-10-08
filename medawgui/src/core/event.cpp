#include "core/event.hpp"

std::bitset<512> Event::keyboardStates;

void Event::keyboardCallback([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
	if (action == GLFW_PRESS)
		keyboardStates[key] = true;

	else if (action == GLFW_RELEASE)
		keyboardStates[key] = false;
}

