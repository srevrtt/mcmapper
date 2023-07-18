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

void mcm_ui_rectangle_draw(UIRectangle *rect, unsigned int shaderProgram) {
  glm_mat4_identity(rect->model);

  vec3 translate = {rect->x + (rect->w / 2), rect->y + (rect->h / 2), 0.0f};
  glm_translate(rect->model, translate);

  vec3 scale = {rect->w, rect->h, 0.0f};
  glm_scale(rect->model, scale);

  rect->color[0] = (float)rect->r/255.0f;
  rect->color[1] = (float)rect->g/255.0f;
  rect->color[2] = (float)rect->b/255.0f;

  int modelLocation = glGetUniformLocation(shaderProgram, "model");
  int colorLocation = glGetUniformLocation(shaderProgram, "color");

  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, rect->model[0]);
  glUniform3fv(colorLocation, 1, rect->color);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
