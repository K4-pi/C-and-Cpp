#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <GL/gl.h>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int heigh);
void processInput(GLFWwindow* window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
        "gl_Position = vec4(aPos, 1.0f);\n"
    "}\0";

const char *fragShaderSourceLeft = "#version 330\n"
    "out vec4 FragColor;\n"
    "uniform vec4 leftColor;\n"
    "void main()\n"
    "{\n"
        //"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "FragColor = leftColor;\n"
    "}\0";

const char *fragShaderSourceRight = "#version 330\n"
    "out vec4 FragColor;\n"
    "uniform vec4 rightColor;\n"
    "void main()\n"
    "{\n"
        //"FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "FragColor = rightColor;\n"
    "}\0";

//Two triagnles in box
// float vertices[] = {
//      0.5f,  0.5f, 0.0f,  // top right
//      0.5f, -0.5f, 0.0f,  // bottom right
//     -0.5f, -0.5f, 0.0f,  // bottom left
//     -0.5f,  0.5f, 0.0f   // top left
// };

//Two triangles near themselfs
// float vertices[] = {
//   -0.5f, 0.0f, 0.0f,
//   0.0f, 0.0f, 0.0f,
//   0.0f, 0.5f, 0.0f,
//   0.5f, 0.0f, 0.0f,
//   0.0f, 0.0f, 0.0f,
//   0.0f, 0.5f, 0.0f
// };

float vertices[] = {
  -0.5f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,
  0.0f, 0.5f, 0.0f,
};

float vertices2[] = {
  0.5f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,
  0.0f, 0.5f, 0.0f
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

unsigned int VBO[2];
unsigned int VAO[2];
unsigned int EBO;
unsigned int vertexShader;
unsigned int fragShader[2];
unsigned int shaderProgramRight;
unsigned int shaderProgramLeft;
// unsigned int shaderProgram;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "First OpenGL", NULL, NULL);
  if (window == NULL)
  {
    printf("Faild to create window!\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD");
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Vertex shader POINTS
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
    memset(infoLog, 0, 512);
  }

  // Fragment shader COLORS
  fragShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader[0], 1, &fragShaderSourceLeft, NULL);
  glCompileShader(fragShader[0]);

  shaderProgramLeft = glCreateProgram();
  glAttachShader(shaderProgramLeft, vertexShader);
  glAttachShader(shaderProgramLeft, fragShader[0]);
  glLinkProgram(shaderProgramLeft);
  glGetProgramiv(shaderProgramLeft, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgramRight, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
    memset(infoLog, 0, 512);
  }

  // Shader program
  // shaderProgram = glCreateProgram();
  // glAttachShader(shaderProgram, fragShader[0]);
  // glAttachShader(shaderProgram, fragShader[1]);
  // glLinkProgram(shaderProgram);
  // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  // if (!success)
  // {
  //   glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  //   printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
  //   memset(infoLog, 0, 512);
  // }

  fragShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader[1], 1, &fragShaderSourceRight, NULL);
  glCompileShader(fragShader[1]);

  shaderProgramRight = glCreateProgram();
  glAttachShader(shaderProgramRight, vertexShader);
  glAttachShader(shaderProgramRight, fragShader[1]);
  glLinkProgram(shaderProgramRight);
  glGetProgramiv(shaderProgramRight, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgramRight, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
    memset(infoLog, 0, 512);
  }

  // Delete shaders after linking to the shader program because we don't need them anymore
  glDeleteShader(vertexShader);
  glDeleteShader(fragShader[0]);
  glDeleteShader(fragShader[1]);

  //--------------------first triangle
  // Vertex array
  glGenVertexArrays(1, &VAO[0]);
  glBindVertexArray(VAO[0]);

  // Vertex buffer
  glGenBuffers(1, &VBO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Element buffer object
  // glGenBuffers(1, &EBO);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //--------------------second triangle
  glGenVertexArrays(1, &VAO[1]);
  glBindVertexArray(VAO[1]);

  glGenBuffers(1, &VBO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  while(!glfwWindowShouldClose(window))
  {
    // Input
    processInput(window);

    // Rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = glfwGetTime();
    float rColor = (std::sin(timeValue / 2.0f)) + 0.5f;
    float gColor = (std::cos(timeValue / 2.0f)) + 0.5f;
    float bColor = (std::sin(timeValue / 2.0f)) - 0.5f;

    int rightShaderProgramUniform = glGetUniformLocation(shaderProgramLeft, "leftColor");
    int leftShaderProgramUniform = glGetUniformLocation(shaderProgramRight, "rightColor");

    glUseProgram(shaderProgramLeft);
    glUniform4f(rightShaderProgramUniform, rColor, gColor, bColor, 1.0f);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramRight);
    glUniform4f(leftShaderProgramUniform, bColor, rColor, gColor, 1.0f);
    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Events and buffer swap
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}

// Resize window
void framebuffer_size_callback(GLFWwindow *window, int width, int heigh)
{
  glViewport(0, 0, width, heigh);
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
