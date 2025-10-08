#pragma once

#include "pch.hpp"

class Event
{
public:
	Event() = delete;
	Event(const Event&) = delete;
	~Event() = default;

	static std::bitset<512> keyboardStates;

	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

