#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "include/rectangle.h"

UIRectangle mcm_ui_rectangle_new(int x, int y, int w, int h, int r, int g, int b) {
  UIRectangle rect;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
  rect.r = r;
  rect.g = g;
  rect.b = b;

  return rect;
}

void mcm_ui_rectangle_draw(UIRectangle rect) {
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
