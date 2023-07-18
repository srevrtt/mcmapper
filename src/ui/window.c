
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "include/window.h"
#include "include/renderer.h"

GLFWwindow *mcmWnd = NULL;
mat4 mcmWndProj;

UIRectangle *mcmRectangles;
int mcmRectanglesSize;
int mcmRectanglesUsed;

void mcm_ui_window_new(unsigned int width, unsigned int height, const char *title) {
  if (!mcmWnd) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mcmWnd = glfwCreateWindow(
      width, height, title, NULL, NULL
    );

    if (!mcmWnd) {
      printf("Error: Failed to create a GLFW window!\n");
      exit(1);
    }

    glfwSwapInterval(1);

    glfwMakeContextCurrent(mcmWnd);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, width, height);
    mcm_ui_renderer_init();

    mcmRectanglesSize = 1;
    mcmRectanglesUsed = 0;
    mcmRectangles = malloc(sizeof(UIRectangle));

    glm_ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f, mcmWndProj);
  }
}

void mcm_ui_window_clear() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void mcm_ui_window_draw() {
  mcm_ui_renderer_preDraw();

  int projectionLocation = glGetUniformLocation(mcm_ui_renderer_shaderProgram(), "projection");
  glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, mcmWndProj[0]);

  for (int i = 0; i < mcmRectanglesUsed; i++) {
    mcm_ui_rectangle_draw(&mcmRectangles[i], mcm_ui_renderer_shaderProgram());
  }
}

void mcm_ui_window_display() {
  glfwSwapBuffers(mcmWnd);
}

void mcm_ui_window_update() {
  glfwWaitEvents();
}

void mcm_ui_window_free() {
  glfwDestroyWindow(mcmWnd);
  glfwTerminate();
}

void mcm_ui_window_addRectangle(UIRectangle rect) {
  if (mcmRectanglesSize == mcmRectanglesUsed) {
    mcmRectanglesSize *= 2;
    mcmRectangles = realloc(mcmRectangles, mcmRectanglesSize * sizeof(UIRectangle));
  }

  mcmRectangles[mcmRectanglesUsed++] = rect;
}

int mcm_ui_window_isOpen() {
  return !glfwWindowShouldClose(mcmWnd);
}
