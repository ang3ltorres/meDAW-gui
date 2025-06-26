#pragma once

class Input
{
public:
	Input() = delete;
	Input(const Input&) = delete;
	~Input() = default;

	static std::bitset<512> keyboardStates;

	static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

