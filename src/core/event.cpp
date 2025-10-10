#include "core/event.hpp"

#include "core/graphics.hpp"

using namespace gui;

std::bitset<512> Event::keyboardStates;
std::bitset<8>   Event::mouseStates;
std::function<void()> Event::updateCallback = nullptr;

void Event::resizedCallback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
	Graphics::width  = width;
	Graphics::height = height;

	Graphics::defaultCamera->width  = width;
	Graphics::defaultCamera->height = height;

	Graphics::setRenderTexture();

	if (updateCallback != nullptr)
		updateCallback();

	std::println("{} {}", width, height);
}

void Event::keyboardCallback([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
	if (action == GLFW_PRESS)
		keyboardStates[key] = true;

	else if (action == GLFW_RELEASE)
		keyboardStates[key] = false;

	if (updateCallback != nullptr)
		updateCallback();
}

void Event::mouseCallback(GLFWwindow* window, int button, int action, [[maybe_unused]] int mods)
{
	if (action == GLFW_PRESS)
		mouseStates[button] = true;

	else if (action == GLFW_RELEASE)
		mouseStates[button] = false;

	if (updateCallback != nullptr)
		updateCallback();

	if (action == GLFW_PRESS or action == GLFW_RELEASE)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::println("X:{}, Y:{}", xpos, ypos);
	}
}

