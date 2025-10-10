#pragma once

#include "pch.hpp"

namespace gui::palette
{
	namespace hex
	{
		constexpr std::string_view dark   = "797979FF";
		constexpr std::string_view darker = "282923FF";
		constexpr std::string_view light  = "F8F8F2FF";
		constexpr std::string_view blue   = "66D9EFFF";
		constexpr std::string_view green  = "A6E22EFF";
		constexpr std::string_view purple = "AC80FFFF";
		constexpr std::string_view yellow = "E7DB74FF";
		constexpr std::string_view orange = "FD971FFF";
		constexpr std::string_view pink   = "F42461FF";
	}

	namespace rgb
	{
		constexpr glm::uvec4 dark   = {121, 121, 121, 255}; // #797979FF
		constexpr glm::uvec4 darker = {40,  41,  35, 255};  // #282923FF
		constexpr glm::uvec4 light  = {248, 248, 242, 255}; // #F8F8F2FF
		constexpr glm::uvec4 blue   = {102, 217, 239, 255}; // #66D9EFFF
		constexpr glm::uvec4 green  = {166, 226, 46, 255};  // #A6E22EFF
		constexpr glm::uvec4 purple = {172, 128, 255, 255}; // #AC80FFFF
		constexpr glm::uvec4 yellow = {231, 219, 116, 255}; // #E7DB74FF
		constexpr glm::uvec4 orange = {253, 151, 31, 255};  // #FD971FFF
		constexpr glm::uvec4 pink   = {244, 36,  97, 255};  // #F42461FF
	}
}
