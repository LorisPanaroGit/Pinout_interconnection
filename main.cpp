#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#define WIN_X_SIZE 680.0f
#define WIN_Y_SIZE 480.0f

void draw_circle(unsigned int n_segments, float center_x, float center_y, float radius);

int main() {
    if (!glfwInit()) {
        std::cerr << "Error\n";
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(WIN_X_SIZE, WIN_Y_SIZE, "My window", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "Window failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1); // Enable vertical sync

    // Initialize GLEW (make sure glewInit() is called after creating the GLFW window)
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WIN_X_SIZE, WIN_Y_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIN_X_SIZE / 2, WIN_X_SIZE / 2, -WIN_Y_SIZE / 2, WIN_Y_SIZE / 2, -1.0, 1.0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        draw_circle(1000, 0, 0, 100);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void draw_circle(unsigned int n_segments, float center_x, float center_y, float radius) {
    glColor3f(0.5, 0.7, 0.5);
    glBegin(GL_LINE_LOOP);

    float dTheta, x_coord, y_coord;
    for (unsigned int i = 0; i < n_segments; i++) {
        dTheta = 2.0 * M_PI * static_cast<float>(i) / static_cast<float>(n_segments);
        x_coord = cos(dTheta) * radius;
        y_coord = sin(dTheta) * radius;
        glVertex2f(x_coord + center_x, y_coord + center_y);
    }

    glEnd();
}
