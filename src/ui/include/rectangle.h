
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cglm/cglm.h>

typedef struct {
  int x, y;
  int w, h;
  int r, g, b;

  mat4 model;
  vec3 color;
} UIRectangle;

UIRectangle mcm_ui_rectangle_new(int x, int y, int w, int h, int r, int g, int b);
void mcm_ui_rectangle_draw(UIRectangle *rect, unsigned int shaderProgram);

#endif
