
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "include/window.h"

GLFWwindow *mcmWnd = NULL;

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
  }
}

void mcm_ui_window_clear() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
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

int mcm_ui_window_isOpen() {
  return !glfwWindowShouldClose(mcmWnd);
}
