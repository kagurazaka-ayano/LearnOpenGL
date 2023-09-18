#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <mathObjects/Point3D.h>
#include <managers/ShaderManager.h>

#include <spdlog/spdlog.h>

#define WIDTH 800
#define HEIGHT 600

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

int main()
{
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello OpenGL!", nullptr, nullptr);
    if (window == nullptr){
        std::cout<<"Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    Point3D pointSet[] = {
            Point3D{-0.5f, -0.5f, 0.0},
            Point3D{0.5f, -0.5f, 0.0},
            Point3D{0.0f, 0.5f, 0.0}
    };
    float vertices[9];
    int idx = 0;
    for (const auto& i : pointSet){
        vertices[idx * 3] = i.x;
        vertices[idx * 3 + 1] = i.y;
        vertices[idx * 3 + 2] = i.z;
        idx++;
    }

    // generate VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    int success;
    char errorLog[512];

    auto manager = ShaderManager::Instance();

    // make vert shader content and compile
    auto vertShader = manager->generateVertexObject();


    // make frag shader content and compile
    auto fragShader = manager->generateFragmentObject();

    // make shader program
    unsigned int shaderProgram = manager->generateShaderProgram<2>("main", {vertShader, fragShader});
    glUseProgram(shaderProgram);

    // delete the shaders
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    // make and bind VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // tell gpu how to interpret the data:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);


    // render loop
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // rendering
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);

        // draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();


    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(-1, 1, width, height);
    std::cout<<"framebufferSizeCallback called! "<<width<<" "<<height<<std::endl;
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
