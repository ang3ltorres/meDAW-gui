#pragma once

#include "gui/widget.hpp"

namespace gui
{
	struct TransportBar : public Pane
	{
		TransportBar();
		TransportBar(const TransportBar&) = delete;
		virtual ~TransportBar() override;

		virtual void draw() override;
		Button buttonTest;
	};

	struct ClockDisplays : public Pane
	{
		ClockDisplays();
		ClockDisplays(const ClockDisplays&) = delete;
		virtual ~ClockDisplays() override;

		virtual void draw() override;
	};

	struct ModeSelector : public Pane
	{
		ModeSelector();
		ModeSelector(const ModeSelector&) = delete;
		virtual ~ModeSelector() override;

		//virtual void draw() override;
	};

	struct TopBar : public Pane
	{
		TopBar();
		TopBar(const TopBar&) = delete;
		virtual ~TopBar() override;

		virtual void draw() override;

		TransportBar transportBar;
		ClockDisplays clockDisplays;
	};

	struct Editor
	{
		static void initialize();
		static void finalize();

		static std::vector<Pane*> panes;
		static void repaint();
		static void EVENT_MOUSE_BUTTON();
		static void EVENT_CURSOR_MOVED();
	};
}