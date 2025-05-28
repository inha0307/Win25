#pragma comment(lib, "Opengl32.lib")
#include <stdio.h>
#include <Windows.h>      // QueryPerformanceCounter, QueryPerformanceFrequency ���
#include <GLFW/glfw3.h> // GLFW ���̺귯�� ���
#include <math.h>         // M_PI, sin, cos �Լ� ���

#define M_PI 3.14159265358979323846

typedef struct rgb {
    float rgbIn_r;
    float rgbIn_g;
    float rgbIn_b;
    float rgbOut_r;
    float rgbOut_g;
    float rgbOut_b;
}RGB;

// �Լ� ������Ÿ��
void drawCircle(float cx, float cy, float r, int num_segments, RGB rgb);
void drawEllipse(float cx, float cy, float xRadius, float yRadius, int num_segments, RGB rgb);
void drawLine(float x1, float y1, float x2, float y2, float thickness, RGB rgb);
void drawBulkyLine(float x1, float y1, float x2, float y2, float thickness, float bulgeFactor, int numSegments, RGB color);
void drawDigit(int number, float posX, float posY, float size, float thickness, RGB activeColor, RGB inactiveColor);
void drawSegmentQuad(float x1, float y1, float x2, float y2, float thickness, RGB color);
void drawCharacter(char c, float height, float thickness, RGB color);
const char* getRomanNumeralString(int hour);
float getRomanNumeralWidth(const char* roman, float charHeight);
void drawRomanNumeral(int hour, float centerX, float centerY, float charHeight, float thickness, RGB color);
void drawRomanNumeral2(int hour, float centerX, float centerY, float charHeight, float thickness, RGB color);




int main()
{
    // GLFW ���̺귯�� �ʱ�ȭ
    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "OpenGL Clock", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ���� ����ü ����
    RGB white = { 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f };
    RGB black = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    RGB gray = { 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f };
    RGB red = { 0.7f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f };
    RGB green = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }; // �ð��� ǥ���� ����
    RGB darkGray = { 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f }; // ��Ȱ��ȭ�� ���׸�Ʈ ���� (��ο� ȸ��)
    RGB silver = {  0.35f, 0.35f, 0.35f, 0.15f, 0.15f, 0.15f}; // ��Ȱ��ȭ�� ���׸�Ʈ ���� (��ο� ȸ��)
    RGB wsilver = { 1.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.3f }; // ��Ȱ��ȭ�� ���׸�Ʈ ���� (��ο� ȸ��)
    RGB softGray = { 0.40f, 0.40f, 0.40f, 0.40f, 0.40f, 0.40f }; // ��Ȱ��ȭ�� ���׸�Ʈ ���� (��ο� ȸ��)
    RGB soft2Gray = { 0.60f, 0.60f, 0.60f, 0.60f, 0.60f, 0.60f }; // ��Ȱ��ȭ�� ���׸�Ʈ ���� (��ο� ȸ��)
    RGB darksilver = { 0.1f, 0.1f, 0.1f, 0.35f, 0.35f, 0.35f }; // ��Ȱ��ȭ�� ���׸�Ʈ ���� (��ο� ȸ��)

    LARGE_INTEGER frequency;
    LARGE_INTEGER startTime;
    LARGE_INTEGER currentTime;

    // ���� ī������ ���ļ��� ���ɴϴ�.
    if (!QueryPerformanceFrequency(&frequency)) {
        printf("���� ī���͸� �������� �ʽ��ϴ�.\n");
        // GLFW ���� �� ���α׷� ���� ó��
        glfwTerminate();
        return 1;
    }

    // ���α׷� ���� ������ ī���� ���� ����մϴ�.
    QueryPerformanceCounter(&startTime);
    float k = 0.5;
    float hour1_posX = -0.25f*k; // ���� ���� �ڸ�
    float hour2_posX = -0.1f*k; // ���� ���� �ڸ�
    float colon_posX = 0.0f; // �ݷ� ��ġ
    float minute1_posX = 0.1f*k; // ���� ���� �ڸ�
    float minute2_posX = 0.25f*k; // ���� ���� �ڸ�
    float digit_posY = -0.4f;   // ������ Y ��ġ (���� �߾�)
    float digit_size = 0.2f*k;   // ������ ũ�� ����
    float digit_thickness = 0.015f* k; // ���ڸ� �����ϴ� �� �β�
    float colon_dot_size = 0.01f*k; // �ݷ� �� ũ��

    float romanNumeralRadius = 0.81f; // �ð� �߽ɿ��� �θ��� ���ڱ����� �Ÿ�
    float numeralCharHeight = 0.07f;  // �θ��� �� ������ ����
    float numeralThickness = 0.01f; // �θ��� ���ڸ� �����ϴ� ���� �β�
    int i; // �ݺ��� ���� ���� (�ʿ信 ���� �ݺ��� ������ �̵� ����)



    // ���� ����
    while (!glfwWindowShouldClose(window))
    {
        QueryPerformanceCounter(&currentTime);

        // ���α׷� ���� ���� �� ��� �ð��� �� ���� (double) �� ����մϴ�.
        double totalElapsedTime = (double)(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;

        // �� ��� �ð��� �������� ���� ���� ��, ���� ��, ���� �ø� ����մϴ�.
        int currentTotalSeconds = (int)totalElapsedTime; // �� ��� �ð��� ���� �ʷ� ��ȯ
        int currentHour = (currentTotalSeconds / 3600) % 12; // 12�ð� �������� ���� �� ���
        int currentMinute = (currentTotalSeconds / 60) % 60;   // 0-59 ������ ���� �� ���
        int currentSecond = currentTotalSeconds % 60;   // 0-59 ������ ���� �� ���
        RGB minorTickColor = black; // ��/�� ���� ���� (��û�Ͻ� ��� red ���)
        float defaultMinorTickThickness = 0.008f; // �⺻ ��/�� ���� �β� (��û�Ͻ� ��)
        float minorTickStartR = 0.8f; // ��/�� ������ ���� ������
        float minorTickEndR = 0.9f;   // ��/�� ������ �� ������

        // ===== �ð� �ٴ� ���� ��� (ƽ���� ������ ����) =====

        // 1. ��ħ ���� (�ε巯�� ������ ���� - ��� �ð��� �Ҽ��� ���� ���)
        // 1�ʿ� 6�� ȸ�� (360�� / 60��)
        float secondsHandAngle = (float)currentSecond * 6.0f;


        // 2. ��ħ ���� (ƽ���� ������ - ���� �� ���)
        // 1�п� 6�� ȸ�� (360�� / 60��)
        float minutesHandAngle = (float)currentMinute * 6.0f;

        // 3. ��ħ ���� (ƽ���� ������ - ���� �� ���)
        // 1�ð��� 30�� ȸ�� (360�� / 12�ð�)
        float hoursHandAngle = (float)currentHour * 30.0f;

        // ��ħ�� 0��(����/����)�� �� 12�� ��ġ�� ����Ű���� ����
        if (currentHour == 0) {
            hoursHandAngle = 12.0f * 30.0f; // 360���� ����Ű���� ���� (OpenGL ȸ�������� 0�� ���������� �������� 12�� ǥ��)
        }


        // ��, ���� ���� �ڸ��� ���� �ڸ� ���ڷ� �и�
        int hour1 = currentHour / 10;
        int hour2 = currentHour % 10;
        int minute1 = currentMinute / 10;
        int minute2 = currentMinute % 10;


        // ȭ�� �ʱ�ȭ (���� ����)
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity(); // �𵨺� ����� ���� ��ķ� �ʱ�ȭ

        // �ð� �� �� ���� �׸��� (���� �ڵ�� ����)
        drawCircle(0.0f, 0.0f, 33.0f, 100, white); // ��� ��
        drawCircle(0.0f, 0.0f, 0.96f, 100, black); // ��� ��
        drawCircle(0.0f, 0.0f, 0.9f, 100, wsilver); // ��� ��
        drawCircle(0.0f, 0.0f, 0.68f, 100, black); // ��� ��
        drawCircle(0.0f, 0.0f, 0.65f, 100, black); // ��� ��
        drawCircle(0.0f, 0.0f, 0.64f, 100, softGray); // ��� ��
        drawCircle(0.0f, 0.0f, 0.18f, 100, black); // ��� ��
        drawCircle(0.0f, 0.0f, 0.17f, 100, silver); // ��� ��


        for (i = 0; i < 40; ++i) {
            float minorTickStartR = 0.19f; // ��/�� ������ ���� ������
            float minorTickEndR = 0.62f;   // ��/�� ������ �� ������
            // 5��/5�� ���� (�θ��� �� ���� ��ġ)�� �ǳʶٱ�

            float angle = (float)i * 9.0f; // �ð� ���� ���� (12�� = 0��)
            float angle_rad = angle * M_PI / 180.0f; // ���� ��ȯ

            // ����(�ð� ����, 12��=0��)�� ���� X, Y ��ǥ ��� (Y�� ���� ������ 0��)
            // ������ startR���� endR���� �׸��ϴ�.
            float startX = minorTickStartR * sin(angle_rad);
            float startY = minorTickStartR * cos(angle_rad);
            float endX = minorTickEndR * sin(angle_rad);
            float endY = minorTickEndR * cos(angle_rad);

            // ���� ���ݿ� ������ �β� ����
            float currentThickness = defaultMinorTickThickness * 3; // �⺻ �β� ����


            // drawSegmentQuad �Լ��� ����Ͽ� �β� �ִ� ������ �׸��ϴ�.
            drawBulkyLine(startX, startY, endX, endY, currentThickness, 0.5f, 100, soft2Gray);

        }

        drawLine(-0.34f*k, -0.4f, 0.34f*k, -0.4f, 0.15f, black);


        // ===== �θ��� �� ���� �׸��� =====
        RGB numeralColor = white; // �θ��� ���� ����

        for (int hour = 1; hour <= 12; ++hour) {
            // �� �ð� ��ġ�� �߽� ��ǥ ��� (12�� ������ Y�� ���, �ð� �������� ���� ����)
            // hour 12�� 0��, hour 3�� 90��, hour 6�� 180��, hour 9�� 270��
            float angle_deg = (float)(hour % 12) * 30.0f; // 12�ô� 0, 1�ô� 30��, ..., 11�ô� 330��
            if (hour == 12) angle_deg = 0.0f; // 12�ø� 0���� ����

            float angle_rad = angle_deg * M_PI / 180.0f;

            // �θ��� ���ڸ� ��ġ�� �߽� ��ǥ
            float numeralX = romanNumeralRadius * sin(angle_rad);
            float numeralY = romanNumeralRadius * cos(angle_rad); // Y�� ����� 0���̹Ƿ� cos ���

            // �θ��� ���ڸ� �׸��� �Լ� ȣ��
            drawRomanNumeral(hour, numeralX, numeralY, numeralCharHeight, numeralThickness, numeralColor);
        }




        {
            drawDigit(hour1, hour1_posX, digit_posY, digit_size, digit_thickness, white, darkGray);

            // ���� ���� �ڸ� ���� �׸��� (Ȱ��: red, ��Ȱ��: darkGray)
            drawDigit(hour2, hour2_posX, digit_posY, digit_size, digit_thickness, white, darkGray);

            // �ݷ� �׸��� (�� �ΰ�) - Ȱ�� ���� (red)���� ǥ��
            glColor3f(red.rgbIn_r, red.rgbIn_g, red.rgbIn_b);
            if (currentSecond % 2 == 0 ) { // ���� �ʰ� 0, 2, 4, ... �� �� �ݷ��� �׸��ϴ�.
                glColor3f(red.rgbIn_r, red.rgbIn_g, red.rgbIn_b); // Ȱ�� ���� ���
                drawCircle(colon_posX, digit_posY + digit_size * 0.25f, colon_dot_size*1.5, 20, red); // ���� ��
                drawCircle(colon_posX, digit_posY - digit_size * 0.25f, colon_dot_size*1.5, 20, red); // �Ʒ��� ��
            }

            // ���� ���� �ڸ� ���� �׸��� (Ȱ��: red, ��Ȱ��: darkGray)
            drawDigit(minute1, minute1_posX, digit_posY, digit_size, digit_thickness, white, darkGray);

            // ���� ���� �ڸ� ���� �׸��� (Ȱ��: red, ��Ȱ��: darkGray)
            drawDigit(minute2, minute2_posX, digit_posY, digit_size, digit_thickness, white, darkGray);


        }



        for (i = 0; i < 60; ++i) {
            float minorTickStartR = 0.85f; // ��/�� ������ ���� ������
            float minorTickEndR = 0.78f;   // ��/�� ������ �� ������
            // 5��/5�� ���� (�θ��� �� ���� ��ġ)�� �ǳʶٱ�
            if (i % 5 != 0) {
                float angle = (float)i * 6.0f; // �ð� ���� ���� (12�� = 0��)
                float angle_rad = angle * M_PI / 180.0f; // ���� ��ȯ

                // ����(�ð� ����, 12��=0��)�� ���� X, Y ��ǥ ��� (Y�� ���� ������ 0��)
                // ������ startR���� endR���� �׸��ϴ�.
                float startX = minorTickStartR * sin(angle_rad);
                float startY = minorTickStartR * cos(angle_rad);
                float endX = minorTickEndR * sin(angle_rad);
                float endY = minorTickEndR * cos(angle_rad);

                // ���� ���ݿ� ������ �β� ����
                float currentThickness = defaultMinorTickThickness; // �⺻ �β� ����
                

                // drawSegmentQuad �Լ��� ����Ͽ� �β� �ִ� ������ �׸��ϴ�.
                drawSegmentQuad(startX, startY, endX, endY, currentThickness*2, minorTickColor);
            }
        }

        
        drawCircle(-0.4f, 0.1f, 0.21f, 100, black); // �ð� �߽��� ���� ��
        drawCircle(-0.4f, 0.1f, 0.20f, 100, black); // �ð� �߽��� ���� ��
        drawCircle(-0.4f, 0.1f, 0.19f, 100, silver); // �ð� �߽��� ���� ��

        {
            float pivotX = -0.4f;
            float pivotY = 0.1f;
            float endRelX = 0.0f;
            float endRelY = 0.17f;
            float lineWidth = 0.02f;

            glPushMatrix();
            glTranslatef(pivotX, pivotY, 0.0f);
            int i; // �ݺ��� ���� ���� (�ʿ信 ���� �ݺ��� ������ �̵� ����)
            for (i = 0; i < 60; ++i) {
                // 5��/5�� ���� (�θ��� �� ���� ��ġ)�� �ǳʶٱ�
                if (i % 5 != 0) {
                    float angle = (float)i * 6.0f; // �ð� ���� ���� (12�� = 0��)
                    float angle_rad = angle * M_PI / 180.0f; // ���� ��ȯ

                    // ����(�ð� ����, 12��=0��)�� ���� X, Y ��ǥ ��� (Y�� ���� ������ 0��)
                    // ������ startR���� endR���� �׸��ϴ�.
                    float startX = minorTickStartR/5 * sin(angle_rad);
                    float startY = minorTickStartR/5 * cos(angle_rad);
                    float endX = minorTickEndR/5 * sin(angle_rad);
                    float endY = minorTickEndR/5 * cos(angle_rad);

                    // ���� ���ݿ� ������ �β� ����
                    float currentThickness = defaultMinorTickThickness*0.7; // �⺻ �β� ����


                    // drawSegmentQuad �Լ��� ����Ͽ� �β� �ִ� ������ �׸��ϴ�.
                    drawSegmentQuad(startX*1.1, startY*1.1, endX, endY, currentThickness, white);
                }
                else
                {
                    float angle = (float)i * 6.0f; // �ð� ���� ���� (12�� = 0��)
                    float angle_rad = angle * M_PI / 180.0f; // ���� ��ȯ

                    // ����(�ð� ����, 12��=0��)�� ���� X, Y ��ǥ ��� (Y�� ���� ������ 0��)
                    // ������ startR���� endR���� �׸��ϴ�.
                    float startX = minorTickStartR / 5 * sin(angle_rad);
                    float startY = minorTickStartR / 5 * cos(angle_rad);
                    float endX = minorTickEndR / 5 * sin(angle_rad);
                    float endY = minorTickEndR / 5 * cos(angle_rad);

                    // ���� ���ݿ� ������ �β� ����
                    float currentThickness = defaultMinorTickThickness*1.5; // �⺻ �β� ����


                    // drawSegmentQuad �Լ��� ����Ͽ� �β� �ִ� ������ �׸��ϴ�.
                    drawSegmentQuad(startX, startY, endX, endY, currentThickness, red);
                }
            }



            // ���� secondsHandAngle�� ����Ͽ� ȸ�� (�ð� ���� = -����)

            glRotatef(-secondsHandAngle, 0.0f, 0.0f, 1.0f);
            drawBulkyLine(0.0f, 0.0f, endRelX, endRelY, 0.04f, 0.5f, 100, red);
            glPopMatrix();
        }
        drawCircle(-0.4f, 0.1f, 0.02f, 100, black); // �ð� �߽��� ���� ��
        drawCircle(-0.4f, 0.1f, 0.005f, 100, white); // �ð� �߽��� ���� ��

        // 2. ��ħ �׸��� (���� �ڵ�� ����, minutesHandAngle ���)
        {
            glPushMatrix();
            // ���� minutesHandAngle�� ����Ͽ� ȸ�� (�ð� ���� = -����)
            glRotatef(-minutesHandAngle, 0.0f, 0.0f, 1.0f);
            drawBulkyLine(0.0f, 0.0f, 0.0f, 0.85f, 0.06f, 0.5f, 1000, white);
            
            glPopMatrix();
            // if (minutesHandAngle >= 6.0f) black; // �� ������ �ǹ� ���� �ڵ��̹Ƿ� �����մϴ�.
        }

        // 3. ��ħ �׸��� (���� �ڵ�� ����, hoursHandAngle ���)
        {
            glPushMatrix();
            // ���� hoursHandAngle�� ����Ͽ� ȸ�� (�ð� ���� = -����)
            glRotatef(-hoursHandAngle, 0.0f, 0.0f, 1.0f);
            drawBulkyLine(0.0f, 0.0f, 0.0f, 0.6f, 0.1f, 0.5f, 1000, red);

            glPopMatrix();
        }

       

        drawCircle(0.0f, 0.0f, 0.05f, 100, black); // �ð� �߽��� ���� ��
        drawCircle(0.0f, 0.0f, 0.015f, 100, red); // �ð� �߽��� ���� ��

        // ���� ��ü (ȭ�鿡 �׸� ǥ��)
        glfwSwapBuffers(window);

        // �̺�Ʈ ó�� (������ �̵�, ũ�� ���� ��)
        glfwPollEvents();
    }


    // ������ �� GLFW ����
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// �� �׸��� �Լ� (����� ����)
void drawCircle(float cx, float cy, float r, int num_segments, RGB rgb)
{
    glBegin(GL_TRIANGLE_FAN);

    // �߽��� ���� ����: RGB ����ü�� rgbIn ��� ���
    glColor3f(rgb.rgbIn_r, rgb.rgbIn_g, rgb.rgbIn_b);
    glVertex2f(cx, cy); // ���� �߽� ��ǥ
    int i;
    for (i = 0; i <= num_segments; i++)
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


// �� �׸��� �Լ� (����� ����)
void drawLine(float x1, float y1, float x2, float y2, float thickness, RGB rgb)
{
    // thickness�� �簢���� ������ ����մϴ�.
    float halfThickness = thickness / 2.0f;

    // �� �� ������ ���� ��� (���� �� ����)
    float dx = x2 - x1;
    float dy = y2 - y1;

    // ���� ���� ���
    float length = sqrt(dx * dx + dy * dy);

    // �� ���� ���ų� �ʹ� ������ (���̰� ���� 0�̸�) �׸� �� �����Ƿ� �����մϴ�.
    if (length < 0.00001f) {
        return;
    }

    // ����ȭ�� ���� ���� (���̰� 1�� ����)
    float ndx = dx / length;
    float ndy = dy / length;

    // ����ȭ�� ���� ���� (���� ���͸� 90�� ȸ����Ų ����)
    float pdx = -ndy;
    float pdy = ndx;

    // �簢���� �� ������ ���
    // ������ (x1, y1)���� ���� �������� halfThickness ��ŭ ������ �� ������
    float v1x = x1 - halfThickness * pdx;
    float v1y = y1 - halfThickness * pdy;
    float v2x = x1 + halfThickness * pdx;
    float v2y = y1 + halfThickness * pdy;

    // ���� (x2, y2)���� ���� �������� halfThickness ��ŭ ������ �� ������
    float v3x = x2 + halfThickness * pdx;
    float v3y = y2 + halfThickness * pdy;
    float v4x = x2 - halfThickness * pdx;
    float v4y = y2 - halfThickness * pdy;

    // �簢�� ���� ����
    glColor3f(rgb.rgbIn_r, rgb.rgbIn_g, rgb.rgbIn_b);

    // �簢�� �׸��� (GL_QUADS ���)
    glBegin(GL_QUADS);
    glVertex2f(v1x, v1y); // ù ��° ������ (v1)
    glVertex2f(v2x, v2y); // �� ��° ������ (v2)
    glVertex2f(v3x, v3y); // �� ��° ������ (v3)
    glVertex2f(v4x, v4y); // �� ��° ������ (v4)
    glEnd();
}

void drawBulkyLine(float x1, float y1, float x2, float y2, float thickness, float bulgeFactor, int numSegments, RGB color)
{
    // �� ���� ���ų� �ʹ� ������ �׸��� ����
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);

    if (length < 0.00001f || numSegments < 2) {
        return; // �ּ� 2�� �̻��� ���׸�Ʈ �ʿ�
    }

    // ����ȭ�� ���� ����
    float ndx = dx / length;
    float ndy = dy / length;

    // ����ȭ�� ���� ���� (���� ���͸� 90�� ȸ��)
    float pdx = -ndy;
    float pdy = ndx;

    // �β��� ����
    float halfThickness = thickness / 2.0f;

    // �簢�� ���� ����
    glColor3f(color.rgbIn_r, color.rgbIn_g, color.rgbIn_b);

    // GL_TRIANGLE_STRIP�� ����Ͽ� ��ٸ���/�ﰢ�� ��Ʈ�� ���� �׸���
    glBegin(GL_TRIANGLE_STRIP);

    // ������ ���̸� ���� ���� ������ ���ø�
    for (int i = 0; i < numSegments; ++i) {
        // ���� ���̿� ���� ���� ��ġ ���� (0.0f���� 1.0f����)
        float t = (float)i / (float)(numSegments - 1);

        // ������ �߽ɼ��� ���� �̵��� ���� ���� (px, py)
        float px = x1 + t * dx;
        float py = y1 + t * dy;

        // ���� �������� ���� �������� �󸶳� �������� ��� (����� ������ Ŀ��)
        // 4.0f * t * (1.0f - t)�� t=0�� t=1���� 0�̰� t=0.5���� 1�� 2�� �Լ� ����
        float currentOffset = 4.0f * t * (1.0f - t) * halfThickness * bulgeFactor;

        // ���� �������� ������ �� ������ ���
        float v1x = px - currentOffset * pdx;
        float v1y = py - currentOffset * pdy;
        float v2x = px + currentOffset * pdx;
        float v2y = py + currentOffset * pdy;

        // GL_TRIANGLE_STRIP�� ������ �߰� (���� �߿�: v1, v2, ���� v1, ���� v2...)
        glVertex2f(v1x, v1y);
        glVertex2f(v2x, v2y);
    }

    glEnd();
}

void drawDigit(int number, float posX, float posY, float size, float thickness, RGB activeColor, RGB inactiveColor) {
    // �� ���׸�Ʈ�� Ȱ��ȭ ���θ� ��Ÿ���� �迭 (0-9����)
    // ����: ���, �»��, ����, �߰�, ���ϴ�, ���ϴ�, �ϴ�
    static const _Bool segments[10][7] = {
        {1, 1, 1, 0, 1, 1, 1}, // 0
        {0, 0, 1, 0, 0, 1, 0}, // 1
        {1, 0, 1, 1, 1, 0, 1}, // 2
        {1, 0, 1, 1, 0, 1, 1}, // 3
        {0, 1, 1, 1, 0, 1, 0}, // 4
        {1, 1, 0, 1, 0, 1, 1}, // 5
        {1, 1, 0, 1, 1, 1, 1}, // 6
        {1, 0, 1, 0, 0, 1, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };

    // ���׸�Ʈ�� ����� ��ġ �� ���� (size = 1.0 ����, �β� ��� ����)
    // �� ���׸�Ʈ�� �߽ɼ� ������ (x1, y1), ���� (x2, y2)
    // 0,0�� �������� ������� ��ǥ ��� (���� 1.0, �� 0.5 ���� - �������ֽ� ��ǥ)
    static const float segCoords[7][4] = {
        {-0.25f,  0.5f,  0.25f,  0.5f}, // ���
        {-0.25f,  0.0f, -0.25f,  0.5f}, // �»��
        { 0.25f,  0.0f,  0.25f,  0.5f}, // ����
        {-0.25f,  0.0f,  0.25f,  0.0f}, // �߰�
        {-0.25f, -0.5f, -0.25f,  0.0f}, // ���ϴ�
        { 0.25f, -0.5f,  0.25f,  0.0f}, // ���ϴ�
        {-0.25f, -0.5f,  0.25f, -0.5f}  // �ϴ�
    };

    // ���ڰ� ��ȿ�� ����(0-9)���� Ȯ��
    if (number < 0 || number > 9) {
        return; // ��ȿ���� ���� ���ڴ� �׸��� ����
    }

    // ���� ���ڿ� ���� ���׸�Ʈ Ȱ��ȭ ���� ��������
    const _Bool* currentSegments = segments[number];
    int i;
    // �� ���׸�Ʈ�� ��ȸ�ϸ� �׸���
    for (i = 0; i < 7; ++i) {
        // ����� ���� ����: Ȱ��ȭ ���ο� ���� activeColor �Ǵ� inactiveColor ���
        RGB color = currentSegments[i] ? activeColor : inactiveColor;

        // ���׸�Ʈ�� ����� ������, ���� ��ǥ �������� (size=1.0 ����)
        float x1_rel = segCoords[i][0];
        float y1_rel = segCoords[i][1];
        float x2_rel = segCoords[i][2];
        float y2_rel = segCoords[i][3];

        // ũ�� �� ��ġ ������ ������ ���� ���� ��ǥ ���
        float x1_abs = posX + x1_rel * size;
        float y1_abs = posY + y1_rel * size;
        float x2_abs = posX + x2_rel * size;
        float y2_abs = posY + y2_rel * size;

        // ���׸�Ʈ�� ���� ���� ���
        float dx = x2_abs - x1_abs;
        float dy = y2_abs - y1_abs;

        // ���� ���� ���
        float length = sqrt(dx * dx + dy * dy);

        // ���̰� �ʹ� ª���� �׸��� ���� (���� ����)
        if (length < 0.00001f) {
            continue;
        }

        // ����ȭ�� ���� ����
        float ndx = dx / length;
        float ndy = dy / length;

        // ����ȭ�� ���� ���� (���� ���͸� 90�� ȸ��)
        float pdx = -ndy;
        float pdy = ndx;

        // ������ �������� ��� �Ÿ� ���� (�β��� ����Ͽ� ����, �� ���� Ʃ���� �ʿ��� �� �ֽ��ϴ�)
        // 0.15f�� ���� ���̸�, ������ ũ��� �β��� ���� �����ؾ� �մϴ�.
        // �۰� �ϸ� ƴ�� ��������, ũ�� �ϸ� ƴ�� �о����ϴ�.
        float retract = thickness * 0.15f;

        // �������� ����� �������� ���� ���
        float x1_adj = x1_abs + ndx * retract;
        float y1_adj = y1_abs + ndy * retract;
        float x2_adj = x2_abs - ndx * retract;
        float y2_adj = y2_abs - ndy * retract;

        // �簢���� ���� �β� ���
        float halfThickness = thickness / 2.0f;

        // �簢���� �� ������ ��� (�������� ����� ������/���� ����)
        float v1x = x1_adj - halfThickness * pdx;
        float v1y = y1_adj - halfThickness * pdy;
        float v2x = x1_adj + halfThickness * pdx;
        float v2y = y1_adj + halfThickness * pdy;
        float v3x = x2_adj + halfThickness * pdx;
        float v3y = y2_adj + halfThickness * pdy;
        float v4x = x2_adj - halfThickness * pdx;
        float v4y = y2_adj - halfThickness * pdy;

        // �簢�� ���� ����
        glColor3f(color.rgbIn_r, color.rgbIn_g, color.rgbIn_b);

        // �簢�� �׸��� (GL_QUADS ���)
        glBegin(GL_QUADS);
        glVertex2f(v1x, v1y);
        glVertex2f(v2x, v2y);
        glVertex2f(v3x, v3y);
        glVertex2f(v4x, v4y);
        glEnd();
    }
}

void drawSegmentQuad(float x1, float y1, float x2, float y2, float thickness, RGB color)
{
    float halfThickness = thickness / 2.0f;
    float dx = x2 - x1;
    float dy = y2 - y1;

    // ���̰� 0�̸� �׸��� ����
    if (dx == 0.0f && dy == 0.0f) {
        return;
    }

    // ������ ����ȭ�� ���� ���Ϳ� ���� ���� ���
    float length = sqrt(dx * dx + dy * dy);
    float ndx = dx / length;
    float ndy = dy / length;
    float pdx = -ndy; // ���� ����
    float pdy = ndx;

    // �簢���� �� ������ ���
    float v1x = x1 - halfThickness * pdx;
    float v1y = y1 - halfThickness * pdy;
    float v2x = x1 + halfThickness * pdx;
    float v2y = y1 + halfThickness * pdy;
    float v3x = x2 + halfThickness * pdx;
    float v3y = y2 + halfThickness * pdy;
    float v4x = x2 - halfThickness * pdx;
    float v4y = y2 - halfThickness * pdy;

    glColor3f(color.rgbIn_r, color.rgbIn_g, color.rgbIn_b);

    glBegin(GL_QUADS);
    glVertex2f(v1x, v1y);
    glVertex2f(v2x, v2y);
    glVertex2f(v3x, v3y);
    glVertex2f(v4x, v4y);
    glEnd();
}

// ���ڸ� �߽� (0,0) �������� �׸��� �Լ�
void drawCharacter(char c, float height, float thickness, RGB color) {
    float halfHeight = height / 2.0f;
    float charWidth = height * 0.8f; // ������ �� (���̿� ����Ͽ� �뷫 ����)
    float halfWidth = charWidth / 2.0f;

    // ���� ���� (RGB ����ü�� ����ϴ� ������ ����)
    glColor3f(color.rgbIn_r, color.rgbIn_g, color.rgbIn_b);

    if (c == 'I') {
        // 'I'�� ������ �ϳ��� (0, -halfHeight)���� (0, halfHeight)�� �׸��ϴ�.
        drawSegmentQuad(0, -halfHeight, 0, halfHeight, thickness, color);
    }
    else if (c == 'V') {
        // 'V'�� �� ���� �밢���� (0,0) �������� �׸��ϴ�.
        // (0,0) ����: �»�� (-halfWidth, halfHeight), �ϴ� (0, -halfHeight), ���� (halfWidth, halfHeight)
        drawSegmentQuad(-halfWidth, halfHeight, 0, -halfHeight, thickness, color); // �»�� -> �ϴ�
        drawSegmentQuad(0, -halfHeight, halfWidth, halfHeight, thickness, color); // �ϴ� -> ����
    }
    else if (c == 'X') {
        // 'X'�� �����ϴ� �� ���� �밢���� (0,0) �������� �׸��ϴ�.
        // (0,0) ����: �»�� (-halfWidth, halfHeight), ���ϴ� (halfWidth, -halfHeight)
        // ���ϴ� (-halfWidth, -halfHeight), ���� (halfWidth, halfHeight)
        drawSegmentQuad(-halfWidth, halfHeight, halfWidth, -halfHeight, thickness, color); // �»�� -> ���ϴ�
        drawSegmentQuad(-halfWidth, -halfHeight, halfWidth, halfHeight, thickness, color); // ���ϴ� -> ����
    }
    // �ٸ� ���ڰ� �ʿ��ϴٸ� ���⿡ �߰�
}


const char* getRomanNumeralString(int hour) {
    switch (hour) {
    case 1: return "I";
    case 2: return "II";
    case 3: return "III";
    case 4: return "IV";
    case 5: return "V";
    case 6: return "VI";
    case 7: return "VII";
    case 8: return "VIII";
    case 9: return "IX";
    case 10: return "X";
    case 11: return "XI";
    case 12: return "XII";
    default: return ""; // 1-12�� �ƴ� ��� �� ���ڿ� ��ȯ
    }
}

float getRomanNumeralWidth(const char* roman, float charHeight) {
    float width = 0;
    float charSpacing = charHeight * 0.1f; // ���� ���� ����
    float iWidth = charHeight * 0.2f; // 'I'�� ��
    float vxWidth = charHeight * 0.8f; // 'V', 'X'�� �� (drawCharacter���� ����� ��)

    int len = 0;
    while (roman[len] != '\0') {
        len++;
    }

    for (int j = 0; j < len; ++j) {
        if (roman[j] == 'I') width += iWidth;
        else if (roman[j] == 'V' || roman[j] == 'X') width += vxWidth;

        if (j < len - 1) width += charSpacing; // ������ ���ڰ� �ƴϸ� ���� �߰�
    }
    // �� ����� �� �����ϰ� �Ϸ��� �� ������ ���� ���� �����ϰų� �̸� �����ؾ� ��
    // ���⼭�� ������ ���� ���� �뷫���� ��� ������ ��� (���� ����Ȯ�� �� ����)
    if (len > 0) {
        // ���� �� * �뷫���� ��� ���� �� + (���� �� - 1) * ����
        return (float)len * (charHeight * 0.5f) + (float)(len - 1) * charSpacing;
    }
    return 0;
}

// ���� �ð�(hour)�� �ش��ϴ� �θ��� ���ڿ��� Ư�� ��ġ(centerX, centerY)��
// �ð� ���⿡ ���� ȸ���Ͽ� �׸��� �Լ� (angle �ڵ� ���)
void drawRomanNumeral(int hour, float centerX, float centerY, float charHeight, float thickness, RGB color) {
    const char* roman = getRomanNumeralString(hour);
    if (roman[0] == '\0' || hour < 1 || hour > 12) return; // ��ȿ���� ���� �ð� �Ǵ� ����

    // �ð� ���� ���
    // 12�ð� ����(0��)�̶�� �����ϰ� �ð� �������� ������ �����Ѵٰ� ������ ��
    // (Ȥ�� ���� 0��, �ð� �������� ���� ���� ������ ������ ���� �ֽ��ϴ�. OpenGL�� glRotatef ���⿡ ���� ���� �ʿ�)
    // ���⼭�� 12�ø� 0����, 1�ø� -30����, 3�ø� -90���� ����ϰڽ��ϴ�.
    // �� �ð� ��ġ�� 360�� / 12 = 30�� �����Դϴ�.
    // �ð� 12�� 0�� �Ǵ� 360��, �ð� 1�� 30��, �ð� 2�� 60�� ... �ð� 11�� 330���� �ش��մϴ�.
    // �ð� ������ �Ϲ������� ����(12��)�� 0���� ���� �ð� �������� �����մϴ�.
    // OpenGL�� glRotatef�� �⺻������ Z�� ���� ����(ȭ���� �հ� ������ ����)���� ���� ��
    // �ݽð� �������� ȸ���ϴ� ���� ��� �����Դϴ�.
    // ���� �ð� �������� ȸ����Ű���� ������ -1�� ���ϰų�, ������ 360���� ���־�� �մϴ�.
    // ���⼭�� �ð� ������ ����� �� OpenGL ȸ���� ���� ���� ������ ��ȯ�Ͽ� ����ϰڽ��ϴ�.

    float angle_degrees;
    if (hour == 12) {
        angle_degrees = 0.0f; // 12�ô� ���� (0��)
    }
    else {
        // 1�� -> 30��, 2�� -> 60��, ..., 11�� -> 330��
        angle_degrees = (float)hour * 30.0f;
    }

    // OpenGL�� �ݽð� ������ ����̹Ƿ�, �ð� ���� ȸ���� ���� ������ -1�� ���մϴ�.
    float rotation_angle_opengl = -angle_degrees;

    // �������ʹ� ���� �ڵ�� �����ϰ� �θ��� ��� ��ü�� ȸ���� ���� ��ǥ�迡�� �׸��ϴ�.

    float totalWidth = getRomanNumeralWidth(roman, charHeight);
    float charSpacing = charHeight * 0.1f;
    float iWidth = charHeight * 0.2f;
    float vxWidth = charHeight * 0.8f;

    glPushMatrix(); // ���� ��ȯ ��� ����

    // 1. �ð��� �ð� ��ġ(��ü �θ��� ����� �߽��� ���� ��ġ)�� �̵�
    glTranslatef(centerX, centerY, 0.0f);

    // 2. ���� ������ ���� ��ü �θ��� ��� ȸ��
    glRotatef(rotation_angle_opengl, 0, 0, 1);

    // 3. ȸ���� ���� ��ǥ�� (X���� ������ ����)���� �� ���ڸ� �������� ��ġ�� ���� X ��ġ ���
    float startX_local = -totalWidth / 2.0f;
    float currentX_local = startX_local;

    int len = 0;
    while (roman[len] != '\0') {
        len++;
    }

    for (int j = 0; j < len; ++j) {
        char currentChar = roman[j];
        float currentCharWidth = 0;

        if (currentChar == 'I') currentCharWidth = iWidth;
        else if (currentChar == 'V' || currentChar == 'X') currentCharWidth = vxWidth;
        else continue;

        float charCenterX_local = currentX_local + currentCharWidth / 2.0f;

        glPushMatrix(); // ���� (�̵� �� ȸ����) ��� ����
        glTranslatef(charCenterX_local, 0, 0); // ���� X ��ġ�� �̵�

        // ���ڸ� �׸��ϴ�. drawCharacter_Local �Լ��� (0,0)�� �������� �׸��ϴ�.
        drawCharacter(currentChar, charHeight, thickness, color);

        glPopMatrix(); // ���ڸ� �׸� �� ��� ����

        currentX_local += currentCharWidth + charSpacing;
    }

    glPopMatrix(); // ��ü �θ��� ��� �׸� �� ó�� ��� ����
}

// drawCharacter_Local, getRomanNumeralString, getRomanNumeralWidth �Լ��� ������ �����ϰ� ����մϴ�.


void drawRomanNumeral2(int hour, float centerX, float centerY, float charHeight, float thickness, RGB color) {
    const char* roman = getRomanNumeralString(hour);
    if (roman[0] == '\0') return; // ��ȿ���� ���� �ð�

    // �θ��� ��ü ���ڿ��� �뷫���� �� ���
    float totalWidth = getRomanNumeralWidth(roman, charHeight);
    float charSpacing = charHeight * 0.1f; // ���� ���� ����
    float iWidth = charHeight * 0.2f; // 'I'�� ��
    float vxWidth = charHeight * 0.8f; // 'V', 'X'�� ��

    // ù ��° ������ ���� X ��ġ (�θ��� ����� �߽� ����)
    float startX = centerX - totalWidth / 2.0f;
    float currentX = startX;

    // �� ���ڸ� ��ȸ�ϸ� �׸���
    int len = 0;
    while (roman[len] != '\0') {
        len++;
    }

    for (int j = 0; j < len; ++j) {
        char currentChar = roman[j];
        float currentCharWidth = 0;

        // ���� ������ �� ����
        if (currentChar == 'I') currentCharWidth = iWidth;
        else if (currentChar == 'V' || currentChar == 'X') currentCharWidth = vxWidth;
        else continue; // �������� �ʴ� ����

        // ���� ������ �߽� X ��ǥ ���
        float charCenterX = currentX + currentCharWidth / 2.0f;

        // ���ڸ� �׸��ϴ�.
        drawCharacter(currentChar, charHeight, thickness, color);

        // ���� ������ ���� X ��ġ ������Ʈ
        currentX += currentCharWidth + charSpacing;
    }
}
