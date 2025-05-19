#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <windows.h> // Sleep �Լ��� ����ϱ� ���� �߰��մϴ�.

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "GLFW: Rotating Triangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    float angle_degrees = 0.0f; // ȸ�� ������ ������ ���� (��)
    const float PI = 3.14159265358979323846f;

    while (!glfwWindowShouldClose(window)) {
        // ������ �������� ��ȯ
        float angle_radians = angle_degrees * (PI / 180.0f);

        glClear(GL_COLOR_BUFFER_BIT); // ȭ�� �����

        glBegin(GL_TRIANGLES); // �ﰢ�� �׸��� ����

        // ù ��° ������ (0.0, 1.0) ȸ��
        glColor3f(1.0f, 0.0f, 0.0f); // ������
        glVertex2f(
            0.0f * cos(angle_radians) - 1.0f * sin(angle_radians),
            0.0f * sin(angle_radians) + 1.0f * cos(angle_radians)
        );

        // �� ��° ������ (-0.866, -0.5) ȸ��
        glColor3f(0.0f, 1.0f, 0.0f); // �ʷϻ�
        glVertex2f(
            -0.866f * cos(angle_radians) - (-0.5f) * sin(angle_radians),
            -0.866f * sin(angle_radians) + (-0.5f) * cos(angle_radians)
        );

        // �� ��° ������ (0.866, -0.5) ȸ��
        glColor3f(0.0f, 0.0f, 1.0f); // �Ķ���
        glVertex2f(
            0.866f * cos(angle_radians) - (-0.5f) * sin(angle_radians),
            0.866f * sin(angle_radians) + (-0.5f) * cos(angle_radians)
        );


        glEnd(); // �ﰢ�� �׸��� ��

        // ���� �������� ���� ���� ���� (��: 1���� ����)
        angle_degrees += 1.0f;


        Sleep(10); // ȸ�� �ӵ� ���� (100ms ��� -> 10ms ���� �����Ͽ� �� �ε巯�� ȸ��)

        glfwSwapBuffers(window); // ���� ��ü�Ͽ� ȭ�鿡 ǥ��
        glfwPollEvents(); // �̺�Ʈ ó��
    }

    glfwDestroyWindow(window); // â �ı�
    glfwTerminate(); // GLFW ����
    return 0;
}
