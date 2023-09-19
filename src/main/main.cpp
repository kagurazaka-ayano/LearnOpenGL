#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <mathObjects/Point3D.h>
#include <managers/ShaderManager.h>

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
    auto blueFragShader = manager->generateFragmentObject("lightSlateBlue");
    auto normalShaderProgram = manager->generateShaderProgram<2>("normal", {vertShader, defaultFragShader});
    auto blueShaderProgram = manager->generateShaderProgram<2>("blue", {vertShader, blueFragShader});
    // delete the shaders
    glDeleteShader(vertShader);
    glDeleteShader(defaultFragShader);
    glDeleteShader(blueFragShader);


    std::array<Point3D, 4> vertex_pool{
        Point3D{-0.5, -0.5, 0},
        Point3D{-0.5, 0.5, 0},
        Point3D{0.5, 0.5, 0},
        Point3D{0.5, -0.5, 0}
    };
    
    int idx = 0;
    float vertices[vertex_pool.size() * sizeof(float) * 3];
    for (const auto& i : vertex_pool){
        vertices[idx * 3] = i.x;
        vertices[idx * 3 + 1] = i.y;
        vertices[idx * 3 + 2] = i.z;
        idx++;
    }

    unsigned int indices[] {
        0, 1, 3,
        1, 2, 3
    };
    
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    // key callback
    glfwSetKeyCallback(window, keyCallback);

    GLint polyMode[2];

    // render loop
    while(!glfwWindowShouldClose(window)){
        // input
        processInput(window);

        // clear color and depth buffer when is in wireframe mode
        if (polyMode[0] != GL_FILL) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw triangle
        glUseProgram(normalShaderProgram);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glUseProgram(blueShaderProgram);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

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
