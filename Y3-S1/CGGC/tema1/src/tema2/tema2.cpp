#include "tema2.h"

#include <cstdio>
#include <cstdlib>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow *glfwWindow = nullptr;
unsigned int VAO0, VAO1, VAO2, VBO0, VBO1, VBO2, EBO0, EBO1, EBO2, shaderProgram;
int width = 1000;
int height = 800;

// Dreptunghi
float rectangleCoords[] = {
    0.f, 0.f, 0.f, 1.f,
    1000.f, 0.f, 0.f, 1.f,
    1000.f, 800.f, 0.f, 1.f,
    0.f, 800.f, 0.f, 1.f
};

unsigned int rectangleIdx[] = {0, 1, 2, 2, 3, 0};

// Convex
float p1Coords[] = {
    100.f, 100.f, 0.f, 1.f,
    150.f, 270.f, 0.f, 1.f,
    70.f, 300.f, 0.f, 1.f,
    50.f, 200.f, 0.f, 1.f
};

unsigned int p1Idx[] = {0, 1, 2, 2, 3, 0};

// Concav
float p2Coords[] = {
    700.f, 150.f, 0.f, 1.f,
    900.f, 500.f, 0.f, 1.f, 
    500.f, 600.f, 0.f, 1.f,
    950.f, 300.f, 0.f, 1.f,
    830.f, 400.f, 0.f, 1.f
};

unsigned int p2Idx[] = {3, 4, 0, 3, 4, 1, 1, 2, 4};

int InitGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(width, height, "Tema 2", NULL, NULL);
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

    const char *vertexShaderSource = ReadShader("src/tema2/vertex.glsl");
    const char *fragmentShaderSource = ReadShader("src/tema2/fragment.glsl");

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

void ProcessCoords() {
    for (int i = 0; i < 5; ++i) {
        int idx = 4 * i;
        if (i == 4) {
            p2Coords[idx] /= 1000.f;
            p2Coords[idx + 1] /= 1000.f;
            p2Coords[idx + 2] /= 1000.f;
        } else {
            rectangleCoords[idx] /= 1000.f;
            rectangleCoords[idx + 1] /= 1000.f;
            rectangleCoords[idx + 2] /= 1000.f;
            
            p1Coords[idx] /= 1000.f;
            p1Coords[idx + 1] /= 1000.f;
            p1Coords[idx + 2] /= 1000.f;

            p2Coords[idx] /= 1000.f;
            p2Coords[idx + 1] /= 1000.f;
            p2Coords[idx + 2] /= 1000.f;
        }
    }
}

void InitGL() {
    ProcessCoords();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    CompileShaderProgram(); 

    // Dreptunghi
    glGenVertexArrays(1, &VAO0);
    
    glGenBuffers(1, &VBO0);
    glGenBuffers(1, &EBO0);
    glBindVertexArray(VAO0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleCoords), rectangleCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIdx), rectangleIdx, GL_STATIC_DRAW);

//    printf("%f %f %f %f\n", rectangleCoords[0], rectangleCoords[1], rectangleCoords[2], rectangleCoords[3]);
//    printf("%f %f %f %f\n", rectangleCoords[4], rectangleCoords[5], rectangleCoords[6], rectangleCoords[7]);
//    printf("%f %f %f %f\n", rectangleCoords[8], rectangleCoords[9], rectangleCoords[10], rectangleCoords[11]);
//    printf("%f %f %f %f\n\n\n", rectangleCoords[12], rectangleCoords[13], rectangleCoords[14], rectangleCoords[15]);

//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            printf("%f ", p2Coords[4 * i + j]);
//        }
//
//        printf("\n");
//    }
//    fflush(stdout);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // Convex
    glGenVertexArrays(1, &VAO1);

    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO1);
    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p1Coords), p1Coords, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(p1Idx), p1Idx, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // Concav
    glGenVertexArrays(1, &VAO2);

    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(p2Coords), p2Coords, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(p2Idx), p2Idx, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void UpdateGL() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   
    glBindVertexArray(VAO1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(glfwWindow);
}

void DestroyGL() {
    glDeleteVertexArrays(1, &VAO0);
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);

    glDeleteBuffers(1, &EBO0);
    glDeleteBuffers(1, &EBO1);
    glDeleteBuffers(1, &EBO2);
    
    glDeleteBuffers(1, &VBO0);
    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);
}

void Tema2() {
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

