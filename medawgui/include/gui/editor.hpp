#pragma once

#include "gui.hpp"

namespace gui
{
	struct TransportBar : public Pane
	{
		TransportBar();
		TransportBar(const TransportBar&) = delete;
		virtual ~TransportBar() override;
	};

	struct ClockDisplays : public Pane
	{
		ClockDisplays();
		ClockDisplays(const ClockDisplays&) = delete;
		virtual ~ClockDisplays() override;
	};

	struct ModeSelector : public Pane
	{
		ModeSelector();
		ModeSelector(const ModeSelector&) = delete;
		virtual ~ModeSelector() override;
	};

	struct TopBar : public Pane
	{
		TopBar();
		TopBar(const TopBar&) = delete;
		virtual ~TopBar() override;
	};

	struct Editor
	{
		static void initialize();
		static void finalize();

		static void update();
	};
}