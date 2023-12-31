#include <iostream>
#include <glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>

void draw_rect(GLFWwindow *win) {
    /*glClear -> clears the color bit buffer*/
    glClear(GL_COLOR_BUFFER_BIT);
    /*glColor3f -> set the color of the buffer*/
    glColor3f(0.5, 0.7, 0.3);
    /*glBegin -> specifies the geometry type of the incoming vertices (deprecated: learn VBO and VAO)*/
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f); // Bottom-left vertex
    glVertex2f(0.5f, -0.5f);  // Bottom-right vertex
    glVertex2f(0.5f, 0.5f);   // Top-right vertex
    glVertex2f(-0.5f, 0.5f);  // Top-left vertex
    glEnd();
    /*glfwSwapBuffers -> places the window behing the rectangle, otherwise we don't see any rectangle*/
    glfwSwapBuffers(win);

}

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
        draw_rect(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
