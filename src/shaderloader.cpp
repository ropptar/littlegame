#include "shaderloader.h"
#include "glad/gl.h"
#include <GL/glext.h>
#include <fstream>
#include <iostream>
#include <string>

int success;
char infolog[512];

std::string readFile(const char *path) {
  std::ifstream input(path);
  input.seekg(0, std::ios::end);
  int length = input.tellg();
  input.seekg(std::ios::beg);

  std::cout << "FILE: " << path << "; LENGTH: " << length << std::endl;
  std::string contents(length, '\0');

  input.read(&contents[0], length);
  input.close();

  std::cout << "Read file: " << path << std::endl;
  return contents;
}

GLuint loadShader(const char *shaderPath, int type) {
  std::string shaderSource = readFile(shaderPath);
  const char *shaderSrc = shaderSource.c_str();
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &shaderSrc, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infolog);
    std::cout << "ERROR::SHADER::" << type
              << "::COMPILATION_FAILED: " << infolog << std::endl;
  }

  return shader;
}

GLuint loadShaderProgram(const char *vertexPath, const char *fragmentPath) {
  GLuint vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
  GLuint fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infolog);
    std::cout << "ERROR::SHADERPROGRAM::"
              << "::COMPILATION_FAILED: " << infolog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}