#pragma once

#include "pch.hpp"

namespace gui
{
	struct Event
	{
		Event() = delete;
		Event(const Event&) = delete;
		~Event() = default;
	
		static std::bitset<512> keyboardStates;
		static std::bitset<8> mouseStates;
		static std::function<void()> updateCallback;
		static std::function<void()> cursorMovedCallback;
		static glm::ivec2 cursor;
		
		static void resizedCallback(GLFWwindow *window, int width, int height);
		static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
		static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
	};
}


