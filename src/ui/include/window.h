
#ifndef WINDOW_H
#define WINDOW_H

#include "rectangle.h"

void mcm_ui_window_new(unsigned int width, unsigned int height, const char *title);
void mcm_ui_window_clear();
void mcm_ui_window_draw();
void mcm_ui_window_display();
void mcm_ui_window_update();
void mcm_ui_window_free();

void mcm_ui_window_addRectangle(UIRectangle rect);

int mcm_ui_window_isOpen();

#endif
