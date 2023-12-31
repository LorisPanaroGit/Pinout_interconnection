#include <iostream>
#include <glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>

int main()
{
    GLFWwindow *window;
    if(!glfwInit()) {
        std::cerr << "Error\n";
        exit(-1);
    }
    window = glfwCreateWindow(680, 480, "My window", nullptr, nullptr);
    if(window == nullptr) {
        std::cerr << "Window failed" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
