
#ifndef RECTANGLE_H
#define RECTANGLE_H

typedef struct {
  int x, y;
  int w, h;
  int r, g, b;
} UIRectangle;

UIRectangle mcm_ui_rectangle_new(int x, int y, int w, int h, int r, int g, int b);
void mcm_ui_rectangle_draw(UIRectangle rect);

#endif
