#include <GLFW/glfw3.h>
#include "callback.h"

GLFWwindow* boilerplate() {
	
  GLFWwindow *window;

  glfwSetErrorCallback(error_callback);


  /* Initialize the library */
  if (!glfwInit())
    return nullptr;
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWmonitor* primaryMoniter = glfwGetPrimaryMonitor();
  const GLFWvidmode mode = *glfwGetVideoMode(primaryMoniter);
  int width = mode.width;
  int height = mode.height;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(width, height, "Hello World", primaryMoniter, NULL);
  if (!window) {
glfwTerminate();
    return nullptr;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

	return window;
}
