#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h> 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
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

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  GLuint tex[2];
  glGenTextures(2, tex);


  GLuint elements[] = {0, 1, 2, 2, 3, 0};

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
               GL_STATIC_DRAW);

  float vertices[] = {
      //  Position      Color             Texcoords
      -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
      -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
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

  // texture binding
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex[0]);
  int width, height;
  unsigned char *image = SOIL_load_image("test.png", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);
  glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, tex[1]);
  image = SOIL_load_image("test.png", &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);
  glUniform1i(glGetUniformLocation(shaderProgram, "tex2"), 0);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7,
                        0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7,
                        (void *)(sizeof(GLfloat) * 2));

  GLuint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7,
                        (void *)(sizeof(GLfloat) * 5));

  if (glGetError() != GL_FALSE) {
    std::cout << "error someware " << glGetError() << "\n";
  }

  GLuint trans_mat = glGetUniformLocation(shaderProgram, "model");

  const GLFWvidmode vidmode = *glfwGetVideoMode(glfwGetPrimaryMonitor());

  height = vidmode.height;
  width = vidmode.width;

  glm::mat4 cam_view = glm::lookAt(
      glm::vec3(1.2f, 1.2f, 1.2f),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 0.0f, 1.0f)
  );
  GLint uniView = glGetUniformLocation(shaderProgram, "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(cam_view));

  glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) width/ (float) height, 1.0f, 10.0f);
  GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
  glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
  
  auto t_start = std::chrono::high_resolution_clock::now();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {

    // Calculate transformation
    auto t_now = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
    /* Render here */


    glm::mat4 trans(1.0f);
    trans = glm::rotate(trans, time*glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(trans_mat, 1, GL_FALSE, glm::value_ptr(trans));

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
