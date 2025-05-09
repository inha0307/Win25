#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>

void drawCircle(float cx, float cy, float r, int num_segments) {
    int i;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // 원의 중심
    for (i = 0; i <= num_segments; i++) {
        float angle = 2.0f * 3.14159265358979323846f * (float)i / (float)num_segments; // 각도 계산 (라디안)
        float x = cx + r * cos(angle); // x 좌표 계산
        float y = cy + r * sin(angle); // y 좌표 계산
        glVertex2f(x, y);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: CIRCLE", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    while (!glfwWindowShouldClose(window)) {
        drawCircle(0.0f, 0.0f, 0.5f, 50);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}