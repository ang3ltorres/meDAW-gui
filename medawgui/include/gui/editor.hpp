#pragma once

#include "gui.hpp"

namespace gui
{
	struct TransportBar : public Pane
	{
		TransportBar();
		TransportBar(const TransportBar&) = delete;
		virtual ~TransportBar() override;

		//virtual void draw() override;
		//virtual void update() override;
	};

	struct ClockDisplays : public Pane
	{
		ClockDisplays();
		ClockDisplays(const ClockDisplays&) = delete;
		virtual ~ClockDisplays() override;

		//virtual void draw() override;
		//virtual void update() override;
	};

	struct ModeSelector : public Pane
	{
		ModeSelector();
		ModeSelector(const ModeSelector&) = delete;
		virtual ~ModeSelector() override;

		//virtual void draw() override;
		//virtual void update() override;
	};

	struct TopBar : public Pane
	{
		TopBar();
		TopBar(const TopBar&) = delete;
		virtual ~TopBar() override;

		virtual void draw() override;
		virtual void update() override;
	};

	struct Editor
	{
		static void initialize();
		static void finalize();

		static void update();

		static std::vector<Pane*> panes;
	};
}