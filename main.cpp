#include <iostream>
#include <glew.h>
#include <glut.h>
#include <GLFW/glfw3.h>

#define WIN_X_SIZE 2160.0f
#define WIN_Y_SIZE 1440.0f

/*------------------------------------------*/

/*0--------------------------------------680*/
/*------------------------------------------*/
/*------------------------------------------*/
/*------------------------------------------*/
/*------------------------------------------*/
/*480------------------------------------680*/

/*------------------------------------------*/

double cursX, cursY;
double rectX, rectY;
bool is_dragging;

void draw_rect(GLFWwindow *win);
void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
void mouse_move_callback(GLFWwindow* win, double xpos, double ypos);
float normalize_Xcoords(double to_conv, float screen_size);
float normalize_Ycoords(double to_conv, float screen_size);

int main()
{
    GLFWwindow *window;
    rectX = 0;
    rectY = 0;
    if(!glfwInit()) {
        std::cerr << "Error\n";
        exit(-1);
    }
    window = glfwCreateWindow(WIN_X_SIZE, WIN_Y_SIZE, "My window", nullptr, nullptr);
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
    glBegin(GL_LINE_LOOP);
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
    float x_norm, y_norm;
    if(button == GLFW_MOUSE_BUTTON_LEFT) {
        /*switch if the button is pressed or released*/
        switch(action) {
            /*if pressed -> check if the mouse is inside the rectangle*/
            case GLFW_PRESS:
                /*Step 1: get the current position of the cursor*/
                glfwGetCursorPos(win, &mouseX, &mouseY);
                std::cout << "X: " << mouseX << "; Y: " << mouseY << std::endl;
                x_norm = normalize_Xcoords(mouseX, WIN_X_SIZE);
                y_norm = normalize_Ycoords(mouseY, WIN_Y_SIZE);
                /*Step 2: check if they are inside the rectangle -> maybe use defines*/
                if((x_norm >= (rectX - 0.5f) && x_norm <= (rectX + 0.5f)) && (y_norm >= (rectY - 0.5f) && y_norm <= (rectY + 0.5f))) {
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
    if(is_dragging == true) {
        rectX += (xpos - cursY) / WIN_X_SIZE;
        rectY -= (ypos - cursY) / WIN_Y_SIZE;
        cursX = xpos;
        cursY = ypos;
    }
}

float normalize_Xcoords(double x_to_conv, float screen_size) {
    float fval = 0;
    fval = ((2 * x_to_conv) / screen_size) - 1;
    return fval;
}

float normalize_Ycoords(double to_conv, float screen_size) {
    float fval = 0;
    fval = 1 - ((2 * to_conv) / screen_size);
    return fval;
}
