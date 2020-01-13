#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <cstdio>
#include <cstdlib>

GLFWwindow *glfwWindow = nullptr;
unsigned int VAO, VBO, shaderProgram;
int width = 800;
int height = 600;

glm::mat4 translateMatrix = glm::mat4(1.f);

float vertices[] = {
    -0.5f, -0.5f, 0.f, 1.f,  1.f, 0.f, 0.f, 1.f,
     0.5f, -0.5f, 0.f, 1.f,  0.f, 1.f, 0.f, 1.f,
      0.f,  0.5f, 0.f, 1.f,  0.f, 0.f, 1.f, 1.f
};

int InitGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, "Tema 1", NULL, NULL);
    if (glfwWindow == nullptr) {
        return -1;
    }

    glfwMakeContextCurrent(glfwWindow);
    return 0;
}

void DestroyGLFW() {
    glfwSetWindowShouldClose(glfwWindow, true);
    glfwTerminate();
}

int InitGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    return 0;
}

const char *ReadShader(const char *shaderPath) {
    FILE *fin = fopen(shaderPath, "rb");

    std::fseek(fin, 0, SEEK_END);
    int size = std::ftell(fin);
    std::fseek(fin, 0, SEEK_SET);

    char *shaderSource = (char *) std::calloc(size, 1);
    std::fread(shaderSource, 1, size, fin);

    fclose(fin);
    return shaderSource;
}

int CompileShaderProgram() {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderSource = ReadShader("src/vertex.glsl");
    const char *fragmentShaderSource = ReadShader("src/fragment.glsl");

    //printf("%s\n\n\n%s", vertexShaderSource, fragmentShaderSource);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLchar infoLog[1024];
    GLint success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        printf("%s\n", infoLog);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        printf("%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return 0;
}

void InitGL() {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    CompileShaderProgram(); 

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position parameter for shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    // Color parameter for shader
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof (float),
                          (void *) (4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glPointSize(15.f);
}

void UpdateGL() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
   
    glBindVertexArray(VAO);

    translateMatrix = glm::translate(translateMatrix, glm::vec3(0.001f, 0.f, 0.f));
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(translateMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(glfwWindow);
}

void DestroyGL() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Lab1() {
    int glfwError = InitGLFW();
    if (glfwError) {
        DestroyGLFW();
        printf("Glfw Error\n");
    }

    int gladError = InitGLAD();
    if (gladError) {
        DestroyGLFW();
        printf("Glad Error\n");
    }

    InitGL();
    while (true) {
        UpdateGL();
    }

    DestroyGL();
    DestroyGLFW();
}

