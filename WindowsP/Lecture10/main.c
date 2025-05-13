#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>

void drawCircle(float cx, float cy, float r, int num_segments) 
{
    int i;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(cx, cy);
    for (i = 0; i <= num_segments; i++) 
    {
        float angle = 2.0f * 3.14159265358979323846f * (float)i / (float)num_segments;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x, y);
    }
    glEnd();
}

int main() 
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: CIRCLE", NULL, NULL);

    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) 
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawCircle(0.0f, 0.0f, 0.8f, 100);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
