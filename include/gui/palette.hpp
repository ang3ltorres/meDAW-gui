#pragma once

#include "pch.hpp"

namespace gui::palette
{
	namespace hex
	{
		constexpr std::string_view dark   = "797979";
		constexpr std::string_view darker = "282923";
		constexpr std::string_view light  = "F8F8F2";
		constexpr std::string_view blue   = "66D9EF";
		constexpr std::string_view green  = "A6E22E";
		constexpr std::string_view purple = "AC80FF";
		constexpr std::string_view yellow = "E7DB74";
		constexpr std::string_view orange = "FD971F";
		constexpr std::string_view pink   = "F42461";
	}

	namespace rgb
	{
		constexpr gui::Color dark   = {121, 121, 121};  // #797979
		constexpr gui::Color darker = {40, 41, 35};     // #282923
		constexpr gui::Color light  = {248, 248, 242};  // #F8F8F2
		constexpr gui::Color blue   = {102, 217, 239};  // #66D9EF
		constexpr gui::Color green  = {166, 226, 46};   // #A6E22E
		constexpr gui::Color purple = {172, 128, 255};  // #AC80FF
		constexpr gui::Color yellow = {231, 219, 116};  // #E7DB74
		constexpr gui::Color orange = {253, 151, 31};   // #FD971F
		constexpr gui::Color pink   = {244, 36, 97};    // #F42461
	}
}
