#include "shaderloader.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <glad/gl.h>

float vertices[] = {-.5f, -.5f, .0f, .5f, -.5f, .0f, .0f, .5f, .0f};

GLuint VBO, VAO;

int main() {

  if (!glfwInit()) {
    return -1;
  }
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "dumb little game", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  int version = gladLoadGL(glfwGetProcAddress);
  printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version),
         GLAD_VERSION_MINOR(version));

  //--------------

  glGenBuffers(1, &VBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  GLuint shaderProgram =
      loadShaderProgram("shaders/triangle.vert", "shaders/triangle.frag");

  //--------------

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}