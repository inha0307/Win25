#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#define M_PI 3.14159265358979323846

typedef struct rgb {
    float rgbIn_r;
    float rgbIn_g;
    float rgbIn_b;
    float rgbOut_r;
    float rgbOut_g;
    float rgbOut_b;
}RGB;

void drawCircle(float cx, float cy, float r, int num_segments, RGB rgb);
void drawEllipse(float cx, float cy, float xRadius, float yRadius, int num_segments, RGB rgb);
void drawLine(float x1, float y1, float x2, float y2, float thickness, RGB rgb);

int main()
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "GLFW: CIRCLE", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    RGB eyes = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    RGB face = { 0.1f, 0.5f, 1.0f, 0.1f, 0.5f, 1.0f };
    RGB nois = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    RGB nois_w = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
    RGB line = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        drawEllipse(0.0f, 0.0f, 10.0f, 10.0f, 100, nois_w);
        drawEllipse(0.0f, 0.0f, 0.808f, 0.728f, 100, eyes);
        drawEllipse(0.0f, 0.0f, 0.8f, 0.72f, 100, face);
        drawCircle(0.6f, 0.2f, 0.05f, 100, eyes);
        drawCircle(-0.6f, 0.2f, 0.05f, 100, eyes);
        drawEllipse(-0.15f, -0.25f, 0.17f, 0.15f, 100, nois_w);
        drawEllipse(0.15f, -0.25f, 0.17f, 0.15f, 100, nois_w);
        drawLine(-0.25f, -0.2f, -0.45f, -0.15f, 4.0f, line);
        drawLine(-0.25f, -0.25f, -0.45f, -0.25f, 4.0f, line);
        drawLine(-0.25f, -0.30f, -0.45f, -0.35f, 4.0f, line);
        drawLine(0.25f, -0.2f, 0.45f, -0.15f, 4.0f, line);
        drawLine(0.25f, -0.25f, 0.45f, -0.25f, 4.0f, line);
        drawLine(0.25f, -0.30f, 0.45f, -0.35f, 4.0f, line);
        drawEllipse(0.0f, -0.08f, 0.12f, 0.1f, 100, nois);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void drawCircle(float cx, float cy, float r, int num_segments, RGB rgb)
{
    glBegin(GL_TRIANGLE_FAN);

    // �߽��� ���� ����: RGB ����ü�� rgbIn ��� ���
    glColor3f(rgb.rgbIn_r, rgb.rgbIn_g, rgb.rgbIn_b);
    glVertex2f(cx, cy); // ���� �߽� ��ǥ

    for (int i = 0; i <= num_segments; i++)
    {
        float angle = 2.0f * M_PI * (float)i / (float)num_segments;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);

        // �ܰ��� ���� ����: RGB ����ü�� rgbOut ��� ���
        glColor3f(rgb.rgbOut_r, rgb.rgbOut_g, rgb.rgbOut_b);
        glVertex2f(x, y); // ���� �ܰ��� �߰�
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float xRadius, float yRadius, int num_segments, RGB rgb)
{
    glBegin(GL_TRIANGLE_FAN);

    // Ÿ���� �߽� ���� ����: RGB ����ü�� rgbIn ��� ���
    glColor3f(rgb.rgbIn_r, rgb.rgbIn_g, rgb.rgbIn_b);
    glVertex2f(cx, cy); // Ÿ���� �߽� ��ǥ

    for (int i = 0; i <= num_segments; i++)
    {
        // �� ���׸�Ʈ(����)�� �ش��ϴ� ������ ����մϴ�.
        float angle = 2.0f * M_PI * (float)i / (float)num_segments;

        // Ÿ���� �ܰ��� ��ǥ�� ����մϴ�.
        float x = cx + xRadius * cos(angle);
        float y = cy + yRadius * sin(angle);

        // Ÿ�� �ܰ� ���� ����: RGB ����ü�� rgbOut ��� ���
        glColor3f(rgb.rgbOut_r, rgb.rgbOut_g, rgb.rgbOut_b);
        glVertex2f(x, y); // ���� �ܰ��� �߰�
    }
    glEnd();
}

// �ʿ��� OpenGL ��� ������ �����ؾ� �մϴ�. ��: <GL/glut.h> �Ǵ� <GL/gl.h>, <GL/glu.h>

void drawLine(float x1, float y1, float x2, float y2, float thickness, RGB rgb)
{
    // ���� �β� ����
    glLineWidth(thickness);

    // ���� ���� ���� (RGB �� ���)
    glColor3f(rgb.rgbIn_r, rgb.rgbIn_g, rgb.rgbIn_b);

    // ���� �׸��� ����
    glBegin(GL_LINES);
    // ������ ��ǥ ����
    glVertex2f(x1, y1);
    // ���� ��ǥ ����
    glVertex2f(x2, y2);
    // ���� �׸��� ����
    glEnd();

}