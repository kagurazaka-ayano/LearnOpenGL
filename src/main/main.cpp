#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <managers/ShaderManager.h>
#include <glObjects/Vertex.h>
#include <glObjects/VertexArray.h>

#include <spdlog/spdlog.h>

#define WIDTH 800
#define HEIGHT 800

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void swapFrameMode();

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

    auto manager = ShaderManager::Instance();

    auto vertShader = manager->generateVertexObject();
    auto defaultFragShader = manager->generateFragmentObject();
    auto normalShaderProgram = manager->generateShaderProgram<2>("normal", {vertShader, defaultFragShader});


    VertexArray arr = VertexArray<3>{
        Vertex{0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f},
        Vertex{-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
        Vertex{0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f}
    };

    spdlog::info(sizeof(arr.data));
    
    unsigned int VAO;
    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr.data), arr.data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(normalShaderProgram);

    // key callback
    glfwSetKeyCallback(window, keyCallback);

    float timeOffset = 0.3;

    // render loop
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // clear color and depth buffer when is in wireframe mode
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, VAO);
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
    spdlog::info("framebufferSizeCallback called! ({0}, {1})", width, height);
}

void processInput(GLFWwindow *window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void swapFrameMode(){
    GLint polyMode[2];
    glGetIntegerv(GL_POLYGON_MODE, polyMode);
    if (polyMode[0] == GL_FILL) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) swapFrameMode();
}
