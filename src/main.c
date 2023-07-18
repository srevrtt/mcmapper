
#include <stdio.h>

#include "ui/include/window.h"

int main(int argc, char *argv[]) {
  mcm_ui_window_new(1280, 720, "MCMapper");

  UIRectangle testRect = mcm_ui_rectangle_new(10, 10, 100, 100, 255, 255, 255);
  mcm_ui_window_addRectangle(testRect);

  while (mcm_ui_window_isOpen()) {
    mcm_ui_window_clear();
    mcm_ui_window_draw();
    mcm_ui_window_display();
    mcm_ui_window_update();
  }

  mcm_ui_window_free();
  return 0;
}
