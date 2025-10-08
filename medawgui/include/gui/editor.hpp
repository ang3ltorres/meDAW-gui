#pragma once

#include "gui.hpp"

namespace gui
{
  class TransportBar : public Pane
  {
    
  };

  class ClockDisplays : public Pane
  {
    
  };

  class ModeSelector : public Pane
  {
    
  };

  class Editor
  {
  public:
    static void initialize();
    static void finalize();
  };
}