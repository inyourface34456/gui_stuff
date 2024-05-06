#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "boilerplate.h"
#include "shaders.h"

int main(void) {
  glewExperimental = GL_TRUE;
  GLFWwindow *window = boilerplate();

  glewInit();

  GLuint vbo;  
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  float vertices[] = {
     0.0,  0.5, 
     0.5, -0.5, 
    -0.5, -0.5
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  GLint status_frag;
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status_frag);

  GLint status_vert;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status_vert);

  if (status_frag != GL_TRUE || status_vert != GL_TRUE) {
    std::cout << "shader complation failed";
  }

  char buffer_vert[512];
  char buffer_frag[512];
  glGetShaderInfoLog(vertexShader, 512, NULL, buffer_vert);
  glGetShaderInfoLog(fragmentShader, 512, NULL, buffer_frag);

  info_callback(buffer_vert);
  info_callback(buffer_frag);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glBindFragDataLocation(shaderProgram, 0, "outColor");

  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glEnableVertexAttribArray(posAttrib);


  if (glGetError() != GL_FALSE) {
    std::cout << "error someware" << glGetError() << "\n";
  }

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
	}

  glfwTerminate();
  return 0;
}
