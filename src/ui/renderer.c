
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "../include/util.h"
#include "include/renderer.h"

unsigned int shaderProgram;
unsigned int vao;

void mcm_ui_renderer_init() {
  float vertices[] = {
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  const char *vertexShaderSource = mcm_util_readFile("resources/shaders/rectangle.vs");
  const char *fragmentShaderSource = mcm_util_readFile("resources/shaders/rectangle.fs");

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
  glCompileShader(fragmentShader);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

void mcm_ui_renderer_preDraw() {
  glUseProgram(shaderProgram);
  glBindVertexArray(vao);
}

unsigned int mcm_ui_renderer_shaderProgram() {
  return shaderProgram;
}

unsigned int mcm_ui_renderer_vao() {
  return vao;
}
