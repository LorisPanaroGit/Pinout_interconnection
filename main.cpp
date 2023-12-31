#include <iostream>
#include <glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>

double cursX, cursY;
double rectX, rectY;
bool is_dragging;

void draw_rect(GLFWwindow *win);
void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
void mouse_move_callback(GLFWwindow* win, double xpos, double ypos);

int main()
{
    GLFWwindow *window;
    rectX = 0;
    rectY = 0;
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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    while(!glfwWindowShouldClose(window)) {
        draw_rect(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void draw_rect(GLFWwindow *win) {
    /*glClear -> clears the color bit buffer*/
    glClear(GL_COLOR_BUFFER_BIT);
    /*glColor3f -> set the color of the buffer*/
    glColor3f(0.5, 0.7, 0.3);
    /*glBegin -> specifies the geometry type of the incoming vertices (deprecated: learn VBO and VAO)*/
    glBegin(GL_QUADS);
    glVertex2f(rectX - 0.5f, rectY - 0.5f); // Bottom-left vertex
    glVertex2f(rectX + 0.5f, rectY - 0.5f);  // Bottom-right vertex
    glVertex2f(rectX + 0.5f, rectY + 0.5f);   // Top-right vertex
    glVertex2f(rectX - 0.5f, rectY + 0.5f);  // Top-left vertex
    glEnd();
    /*glfwSwapBuffers -> places the window behing the rectangle, otherwise we don't see any rectangle*/
    glfwSwapBuffers(win);
}

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    double mouseX, mouseY;
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        /*switch if the button is pressed or released*/
        switch(action) {
            /*if pressed -> check if the mouse is inside the rectangle*/
            case GLFW_PRESS:
                /*Step 1: get the cursor coords and save them in mouseX and mouseY*/
                glfwGetCursorPos(win, &mouseX, &mouseY);
                /*Step 2: check if they are inside the rectangle -> maybe use defines*/
                if((mouseX >= (rectX - 0.5f) && mouseX <= (rectX + 0.5f)) && (mouseY >= (rectY -0.5f) && mouseY <= (rectY + 0.5f))) {
                    /*get the position of the cursor at the time it has been pressed*/
                    cursX = mouseX;
                    cursY = mouseY;
                    is_dragging = true;
                } else {
                    is_dragging = false;
                }
                break;
            case GLFW_RELEASE:
                is_dragging = false;
                break;
            default:
                break;
        }
    }
}
void mouse_move_callback(GLFWwindow* win, double xpos, double ypos) {
    if(is_dragging) {
        rectX += (xpos - cursY) / 680.0f;
        rectY -= (ypos - cursY) / 480.0f;
        cursX = xpos;
        cursY = ypos;
    }
}
