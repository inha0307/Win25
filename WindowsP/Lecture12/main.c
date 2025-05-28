#pragma comment(lib, "Opengl32.lib")
#include <stdio.h>
#include <Windows.h>      // QueryPerformanceCounter, QueryPerformanceFrequency 사용
#include <GLFW/glfw3.h> // GLFW 라이브러리 사용
#include <math.h>         // M_PI, sin, cos 함수 사용

#define M_PI 3.14159265358979323846

typedef struct rgb {
    float rgbIn_r;
    float rgbIn_g;
    float rgbIn_b;
    float rgbOut_r;
    float rgbOut_g;
    float rgbOut_b;
}RGB;

// 함수 프로토타입
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
    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "OpenGL Clock", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 색상 구조체 정의
    RGB white = { 0.85f, 0.85f, 0.85f, 0.85f, 0.85f, 0.85f };
    RGB black = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    RGB gray = { 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f };
    RGB red = { 0.7f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f };
    RGB green = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }; // 시간을 표시할 색상
    RGB darkGray = { 0.15f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f }; // 비활성화된 세그먼트 색상 (어두운 회색)
    RGB silver = {  0.35f, 0.35f, 0.35f, 0.15f, 0.15f, 0.15f}; // 비활성화된 세그먼트 색상 (어두운 회색)
    RGB wsilver = { 1.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.3f }; // 비활성화된 세그먼트 색상 (어두운 회색)
    RGB softGray = { 0.40f, 0.40f, 0.40f, 0.40f, 0.40f, 0.40f }; // 비활성화된 세그먼트 색상 (어두운 회색)
    RGB soft2Gray = { 0.60f, 0.60f, 0.60f, 0.60f, 0.60f, 0.60f }; // 비활성화된 세그먼트 색상 (어두운 회색)
    RGB darksilver = { 0.1f, 0.1f, 0.1f, 0.35f, 0.35f, 0.35f }; // 비활성화된 세그먼트 색상 (어두운 회색)

    LARGE_INTEGER frequency;
    LARGE_INTEGER startTime;
    LARGE_INTEGER currentTime;

    // 성능 카운터의 주파수를 얻어옵니다.
    if (!QueryPerformanceFrequency(&frequency)) {
        printf("성능 카운터를 지원하지 않습니다.\n");
        // GLFW 종료 및 프로그램 종료 처리
        glfwTerminate();
        return 1;
    }

    // 프로그램 시작 시점의 카운터 값을 기록합니다.
    QueryPerformanceCounter(&startTime);
    float k = 0.5;
    float hour1_posX = -0.25f*k; // 시의 십의 자리
    float hour2_posX = -0.1f*k; // 시의 일의 자리
    float colon_posX = 0.0f; // 콜론 위치
    float minute1_posX = 0.1f*k; // 분의 십의 자리
    float minute2_posX = 0.25f*k; // 분의 일의 자리
    float digit_posY = -0.4f;   // 숫자의 Y 위치 (세로 중앙)
    float digit_size = 0.2f*k;   // 숫자의 크기 배율
    float digit_thickness = 0.015f* k; // 숫자를 구성하는 선 두께
    float colon_dot_size = 0.01f*k; // 콜론 점 크기

    float romanNumeralRadius = 0.81f; // 시계 중심에서 로마자 숫자까지의 거리
    float numeralCharHeight = 0.07f;  // 로마자 각 문자의 높이
    float numeralThickness = 0.01f; // 로마자 문자를 구성하는 선의 두께
    int i; // 반복문 변수 선언 (필요에 따라 반복문 밖으로 이동 가능)



    // 메인 루프
    while (!glfwWindowShouldClose(window))
    {
        QueryPerformanceCounter(&currentTime);

        // 프로그램 시작 이후 총 경과 시간을 초 단위 (double) 로 계산합니다.
        double totalElapsedTime = (double)(currentTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;

        // 총 경과 시간을 바탕으로 현재 정수 초, 정수 분, 정수 시를 계산합니다.
        int currentTotalSeconds = (int)totalElapsedTime; // 총 경과 시간을 정수 초로 변환
        int currentHour = (currentTotalSeconds / 3600) % 12; // 12시간 형식으로 정수 시 계산
        int currentMinute = (currentTotalSeconds / 60) % 60;   // 0-59 범위의 정수 분 계산
        int currentSecond = currentTotalSeconds % 60;   // 0-59 범위의 정수 초 계산
        RGB minorTickColor = black; // 분/초 눈금 색상 (요청하신 대로 red 사용)
        float defaultMinorTickThickness = 0.008f; // 기본 분/초 눈금 두께 (요청하신 값)
        float minorTickStartR = 0.8f; // 분/초 눈금의 시작 반지름
        float minorTickEndR = 0.9f;   // 분/초 눈금의 끝 반지름

        // ===== 시계 바늘 각도 계산 (틱택토 움직임 적용) =====

        // 1. 초침 각도 (부드러운 움직임 유지 - 경과 시간의 소수점 이하 사용)
        // 1초에 6도 회전 (360도 / 60초)
        float secondsHandAngle = (float)currentSecond * 6.0f;


        // 2. 분침 각도 (틱택토 움직임 - 정수 분 사용)
        // 1분에 6도 회전 (360도 / 60분)
        float minutesHandAngle = (float)currentMinute * 6.0f;

        // 3. 시침 각도 (틱택토 움직임 - 정수 시 사용)
        // 1시간에 30도 회전 (360도 / 12시간)
        float hoursHandAngle = (float)currentHour * 30.0f;

        // 시침이 0시(자정/정오)일 때 12시 위치를 가리키도록 조정
        if (currentHour == 0) {
            hoursHandAngle = 12.0f * 30.0f; // 360도를 가리키도록 설정 (OpenGL 회전에서는 0과 동일하지만 논리적으로 12를 표현)
        }


        // 시, 분을 십의 자리와 일의 자리 숫자로 분리
        int hour1 = currentHour / 10;
        int hour2 = currentHour % 10;
        int minute1 = currentMinute / 10;
        int minute2 = currentMinute % 10;


        // 화면 초기화 (색상 버퍼)
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity(); // 모델뷰 행렬을 단위 행렬로 초기화

        // 시계 얼굴 및 눈금 그리기 (이전 코드와 동일)
        drawCircle(0.0f, 0.0f, 33.0f, 100, white); // 배경 원
        drawCircle(0.0f, 0.0f, 0.96f, 100, black); // 배경 원
        drawCircle(0.0f, 0.0f, 0.9f, 100, wsilver); // 배경 원
        drawCircle(0.0f, 0.0f, 0.68f, 100, black); // 배경 원
        drawCircle(0.0f, 0.0f, 0.65f, 100, black); // 배경 원
        drawCircle(0.0f, 0.0f, 0.64f, 100, softGray); // 배경 원
        drawCircle(0.0f, 0.0f, 0.18f, 100, black); // 배경 원
        drawCircle(0.0f, 0.0f, 0.17f, 100, silver); // 배경 원


        for (i = 0; i < 40; ++i) {
            float minorTickStartR = 0.19f; // 분/초 눈금의 시작 반지름
            float minorTickEndR = 0.62f;   // 분/초 눈금의 끝 반지름
            // 5분/5초 간격 (로마자 시 눈금 위치)는 건너뛰기

            float angle = (float)i * 9.0f; // 시계 방향 각도 (12시 = 0도)
            float angle_rad = angle * M_PI / 180.0f; // 라디안 변환

            // 각도(시계 방향, 12시=0도)에 대한 X, Y 좌표 계산 (Y축 양의 방향이 0도)
            // 눈금은 startR에서 endR까지 그립니다.
            float startX = minorTickStartR * sin(angle_rad);
            float startY = minorTickStartR * cos(angle_rad);
            float endX = minorTickEndR * sin(angle_rad);
            float endY = minorTickEndR * cos(angle_rad);

            // 현재 눈금에 적용할 두께 결정
            float currentThickness = defaultMinorTickThickness * 3; // 기본 두께 적용


            // drawSegmentQuad 함수를 사용하여 두께 있는 눈금을 그립니다.
            drawBulkyLine(startX, startY, endX, endY, currentThickness, 0.5f, 100, soft2Gray);

        }

        drawLine(-0.34f*k, -0.4f, 0.34f*k, -0.4f, 0.15f, black);


        // ===== 로마자 시 눈금 그리기 =====
        RGB numeralColor = white; // 로마자 눈금 색상

        for (int hour = 1; hour <= 12; ++hour) {
            // 각 시간 위치의 중심 좌표 계산 (12시 방향이 Y축 양수, 시계 방향으로 각도 증가)
            // hour 12는 0도, hour 3은 90도, hour 6은 180도, hour 9는 270도
            float angle_deg = (float)(hour % 12) * 30.0f; // 12시는 0, 1시는 30도, ..., 11시는 330도
            if (hour == 12) angle_deg = 0.0f; // 12시를 0도로 설정

            float angle_rad = angle_deg * M_PI / 180.0f;

            // 로마자 숫자를 배치할 중심 좌표
            float numeralX = romanNumeralRadius * sin(angle_rad);
            float numeralY = romanNumeralRadius * cos(angle_rad); // Y축 상단이 0도이므로 cos 사용

            // 로마자 숫자를 그리는 함수 호출
            drawRomanNumeral(hour, numeralX, numeralY, numeralCharHeight, numeralThickness, numeralColor);
        }




        {
            drawDigit(hour1, hour1_posX, digit_posY, digit_size, digit_thickness, white, darkGray);

            // 시의 일의 자리 숫자 그리기 (활성: red, 비활성: darkGray)
            drawDigit(hour2, hour2_posX, digit_posY, digit_size, digit_thickness, white, darkGray);

            // 콜론 그리기 (점 두개) - 활성 색상 (red)으로 표시
            glColor3f(red.rgbIn_r, red.rgbIn_g, red.rgbIn_b);
            if (currentSecond % 2 == 0 ) { // 현재 초가 0, 2, 4, ... 일 때 콜론을 그립니다.
                glColor3f(red.rgbIn_r, red.rgbIn_g, red.rgbIn_b); // 활성 색상 사용
                drawCircle(colon_posX, digit_posY + digit_size * 0.25f, colon_dot_size*1.5, 20, red); // 위쪽 점
                drawCircle(colon_posX, digit_posY - digit_size * 0.25f, colon_dot_size*1.5, 20, red); // 아래쪽 점
            }

            // 분의 십의 자리 숫자 그리기 (활성: red, 비활성: darkGray)
            drawDigit(minute1, minute1_posX, digit_posY, digit_size, digit_thickness, white, darkGray);

            // 분의 일의 자리 숫자 그리기 (활성: red, 비활성: darkGray)
            drawDigit(minute2, minute2_posX, digit_posY, digit_size, digit_thickness, white, darkGray);


        }



        for (i = 0; i < 60; ++i) {
            float minorTickStartR = 0.85f; // 분/초 눈금의 시작 반지름
            float minorTickEndR = 0.78f;   // 분/초 눈금의 끝 반지름
            // 5분/5초 간격 (로마자 시 눈금 위치)는 건너뛰기
            if (i % 5 != 0) {
                float angle = (float)i * 6.0f; // 시계 방향 각도 (12시 = 0도)
                float angle_rad = angle * M_PI / 180.0f; // 라디안 변환

                // 각도(시계 방향, 12시=0도)에 대한 X, Y 좌표 계산 (Y축 양의 방향이 0도)
                // 눈금은 startR에서 endR까지 그립니다.
                float startX = minorTickStartR * sin(angle_rad);
                float startY = minorTickStartR * cos(angle_rad);
                float endX = minorTickEndR * sin(angle_rad);
                float endY = minorTickEndR * cos(angle_rad);

                // 현재 눈금에 적용할 두께 결정
                float currentThickness = defaultMinorTickThickness; // 기본 두께 적용
                

                // drawSegmentQuad 함수를 사용하여 두께 있는 눈금을 그립니다.
                drawSegmentQuad(startX, startY, endX, endY, currentThickness*2, minorTickColor);
            }
        }

        
        drawCircle(-0.4f, 0.1f, 0.21f, 100, black); // 시계 중심의 작은 원
        drawCircle(-0.4f, 0.1f, 0.20f, 100, black); // 시계 중심의 작은 원
        drawCircle(-0.4f, 0.1f, 0.19f, 100, silver); // 시계 중심의 작은 원

        {
            float pivotX = -0.4f;
            float pivotY = 0.1f;
            float endRelX = 0.0f;
            float endRelY = 0.17f;
            float lineWidth = 0.02f;

            glPushMatrix();
            glTranslatef(pivotX, pivotY, 0.0f);
            int i; // 반복문 변수 선언 (필요에 따라 반복문 밖으로 이동 가능)
            for (i = 0; i < 60; ++i) {
                // 5분/5초 간격 (로마자 시 눈금 위치)는 건너뛰기
                if (i % 5 != 0) {
                    float angle = (float)i * 6.0f; // 시계 방향 각도 (12시 = 0도)
                    float angle_rad = angle * M_PI / 180.0f; // 라디안 변환

                    // 각도(시계 방향, 12시=0도)에 대한 X, Y 좌표 계산 (Y축 양의 방향이 0도)
                    // 눈금은 startR에서 endR까지 그립니다.
                    float startX = minorTickStartR/5 * sin(angle_rad);
                    float startY = minorTickStartR/5 * cos(angle_rad);
                    float endX = minorTickEndR/5 * sin(angle_rad);
                    float endY = minorTickEndR/5 * cos(angle_rad);

                    // 현재 눈금에 적용할 두께 결정
                    float currentThickness = defaultMinorTickThickness*0.7; // 기본 두께 적용


                    // drawSegmentQuad 함수를 사용하여 두께 있는 눈금을 그립니다.
                    drawSegmentQuad(startX*1.1, startY*1.1, endX, endY, currentThickness, white);
                }
                else
                {
                    float angle = (float)i * 6.0f; // 시계 방향 각도 (12시 = 0도)
                    float angle_rad = angle * M_PI / 180.0f; // 라디안 변환

                    // 각도(시계 방향, 12시=0도)에 대한 X, Y 좌표 계산 (Y축 양의 방향이 0도)
                    // 눈금은 startR에서 endR까지 그립니다.
                    float startX = minorTickStartR / 5 * sin(angle_rad);
                    float startY = minorTickStartR / 5 * cos(angle_rad);
                    float endX = minorTickEndR / 5 * sin(angle_rad);
                    float endY = minorTickEndR / 5 * cos(angle_rad);

                    // 현재 눈금에 적용할 두께 결정
                    float currentThickness = defaultMinorTickThickness*1.5; // 기본 두께 적용


                    // drawSegmentQuad 함수를 사용하여 두께 있는 눈금을 그립니다.
                    drawSegmentQuad(startX, startY, endX, endY, currentThickness, red);
                }
            }



            // 계산된 secondsHandAngle을 사용하여 회전 (시계 방향 = -각도)

            glRotatef(-secondsHandAngle, 0.0f, 0.0f, 1.0f);
            drawBulkyLine(0.0f, 0.0f, endRelX, endRelY, 0.04f, 0.5f, 100, red);
            glPopMatrix();
        }
        drawCircle(-0.4f, 0.1f, 0.02f, 100, black); // 시계 중심의 작은 원
        drawCircle(-0.4f, 0.1f, 0.005f, 100, white); // 시계 중심의 작은 원

        // 2. 분침 그리기 (이전 코드와 동일, minutesHandAngle 사용)
        {
            glPushMatrix();
            // 계산된 minutesHandAngle을 사용하여 회전 (시계 방향 = -각도)
            glRotatef(-minutesHandAngle, 0.0f, 0.0f, 1.0f);
            drawBulkyLine(0.0f, 0.0f, 0.0f, 0.85f, 0.06f, 0.5f, 1000, white);
            
            glPopMatrix();
            // if (minutesHandAngle >= 6.0f) black; // 이 라인은 의미 없는 코드이므로 제거합니다.
        }

        // 3. 시침 그리기 (이전 코드와 동일, hoursHandAngle 사용)
        {
            glPushMatrix();
            // 계산된 hoursHandAngle을 사용하여 회전 (시계 방향 = -각도)
            glRotatef(-hoursHandAngle, 0.0f, 0.0f, 1.0f);
            drawBulkyLine(0.0f, 0.0f, 0.0f, 0.6f, 0.1f, 0.5f, 1000, red);

            glPopMatrix();
        }

       

        drawCircle(0.0f, 0.0f, 0.05f, 100, black); // 시계 중심의 작은 원
        drawCircle(0.0f, 0.0f, 0.015f, 100, red); // 시계 중심의 작은 원

        // 버퍼 교체 (화면에 그림 표시)
        glfwSwapBuffers(window);

        // 이벤트 처리 (윈도우 이동, 크기 조절 등)
        glfwPollEvents();
    }


    // 윈도우 및 GLFW 종료
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// 원 그리는 함수 (사용자 제공)
void drawCircle(float cx, float cy, float r, int num_segments, RGB rgb)
{
    glBegin(GL_TRIANGLE_FAN);

    // 중심점 색상 설정: RGB 구조체의 rgbIn 멤버 사용
    glColor3f(rgb.rgbIn_r, rgb.rgbIn_g, rgb.rgbIn_b);
    glVertex2f(cx, cy); // 원의 중심 좌표
    int i;
    for (i = 0; i <= num_segments; i++)
    {
        float angle = 2.0f * M_PI * (float)i / (float)num_segments;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);

        // 외곽점 색상 설정: RGB 구조체의 rgbOut 멤버 사용
        glColor3f(rgb.rgbOut_r, rgb.rgbOut_g, rgb.rgbOut_b);
        glVertex2f(x, y); // 계산된 외곽점 추가
    }
    glEnd();
}


// 선 그리는 함수 (사용자 제공)
void drawLine(float x1, float y1, float x2, float y2, float thickness, RGB rgb)
{
    // thickness를 사각형의 폭으로 사용합니다.
    float halfThickness = thickness / 2.0f;

    // 두 점 사이의 벡터 계산 (방향 및 길이)
    float dx = x2 - x1;
    float dy = y2 - y1;

    // 벡터 길이 계산
    float length = sqrt(dx * dx + dy * dy);

    // 두 점이 같거나 너무 가까우면 (길이가 거의 0이면) 그릴 수 없으므로 종료합니다.
    if (length < 0.00001f) {
        return;
    }

    // 정규화된 방향 벡터 (길이가 1인 벡터)
    float ndx = dx / length;
    float ndy = dy / length;

    // 정규화된 수직 벡터 (방향 벡터를 90도 회전시킨 벡터)
    float pdx = -ndy;
    float pdy = ndx;

    // 사각형의 네 꼭짓점 계산
    // 시작점 (x1, y1)에서 수직 방향으로 halfThickness 만큼 떨어진 두 꼭짓점
    float v1x = x1 - halfThickness * pdx;
    float v1y = y1 - halfThickness * pdy;
    float v2x = x1 + halfThickness * pdx;
    float v2y = y1 + halfThickness * pdy;

    // 끝점 (x2, y2)에서 수직 방향으로 halfThickness 만큼 떨어진 두 꼭짓점
    float v3x = x2 + halfThickness * pdx;
    float v3y = y2 + halfThickness * pdy;
    float v4x = x2 - halfThickness * pdx;
    float v4y = y2 - halfThickness * pdy;

    // 사각형 색상 설정
    glColor3f(rgb.rgbIn_r, rgb.rgbIn_g, rgb.rgbIn_b);

    // 사각형 그리기 (GL_QUADS 사용)
    glBegin(GL_QUADS);
    glVertex2f(v1x, v1y); // 첫 번째 꼭짓점 (v1)
    glVertex2f(v2x, v2y); // 두 번째 꼭짓점 (v2)
    glVertex2f(v3x, v3y); // 세 번째 꼭짓점 (v3)
    glVertex2f(v4x, v4y); // 네 번째 꼭짓점 (v4)
    glEnd();
}

void drawBulkyLine(float x1, float y1, float x2, float y2, float thickness, float bulgeFactor, int numSegments, RGB color)
{
    // 두 점이 같거나 너무 가까우면 그리지 않음
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = sqrt(dx * dx + dy * dy);

    if (length < 0.00001f || numSegments < 2) {
        return; // 최소 2개 이상의 세그먼트 필요
    }

    // 정규화된 방향 벡터
    float ndx = dx / length;
    float ndy = dy / length;

    // 정규화된 수직 벡터 (방향 벡터를 90도 회전)
    float pdx = -ndy;
    float pdy = ndx;

    // 두께의 절반
    float halfThickness = thickness / 2.0f;

    // 사각형 색상 설정
    glColor3f(color.rgbIn_r, color.rgbIn_g, color.rgbIn_b);

    // GL_TRIANGLE_STRIP을 사용하여 사다리꼴/삼각형 스트립 형태 그리기
    glBegin(GL_TRIANGLE_STRIP);

    // 선분의 길이를 따라 여러 지점을 샘플링
    for (int i = 0; i < numSegments; ++i) {
        // 선분 길이에 대한 현재 위치 비율 (0.0f에서 1.0f까지)
        float t = (float)i / (float)(numSegments - 1);

        // 선분의 중심선을 따라 이동한 현재 지점 (px, py)
        float px = x1 + t * dx;
        float py = y1 + t * dy;

        // 현재 지점에서 수직 방향으로 얼마나 떨어질지 계산 (가운데로 갈수록 커짐)
        // 4.0f * t * (1.0f - t)는 t=0과 t=1에서 0이고 t=0.5에서 1인 2차 함수 형태
        float currentOffset = 4.0f * t * (1.0f - t) * halfThickness * bulgeFactor;

        // 수직 방향으로 떨어진 두 꼭짓점 계산
        float v1x = px - currentOffset * pdx;
        float v1y = py - currentOffset * pdy;
        float v2x = px + currentOffset * pdx;
        float v2y = py + currentOffset * pdy;

        // GL_TRIANGLE_STRIP에 꼭짓점 추가 (순서 중요: v1, v2, 다음 v1, 다음 v2...)
        glVertex2f(v1x, v1y);
        glVertex2f(v2x, v2y);
    }

    glEnd();
}

void drawDigit(int number, float posX, float posY, float size, float thickness, RGB activeColor, RGB inactiveColor) {
    // 각 세그먼트의 활성화 여부를 나타내는 배열 (0-9까지)
    // 순서: 상단, 좌상단, 우상단, 중간, 좌하단, 우하단, 하단
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

    // 세그먼트의 상대적 위치 및 길이 (size = 1.0 기준, 두께 고려 안함)
    // 각 세그먼트의 중심선 시작점 (x1, y1), 끝점 (x2, y2)
    // 0,0을 기준으로 상대적인 좌표 사용 (높이 1.0, 폭 0.5 기준 - 제공해주신 좌표)
    static const float segCoords[7][4] = {
        {-0.25f,  0.5f,  0.25f,  0.5f}, // 상단
        {-0.25f,  0.0f, -0.25f,  0.5f}, // 좌상단
        { 0.25f,  0.0f,  0.25f,  0.5f}, // 우상단
        {-0.25f,  0.0f,  0.25f,  0.0f}, // 중간
        {-0.25f, -0.5f, -0.25f,  0.0f}, // 좌하단
        { 0.25f, -0.5f,  0.25f,  0.0f}, // 우하단
        {-0.25f, -0.5f,  0.25f, -0.5f}  // 하단
    };

    // 숫자가 유효한 범위(0-9)인지 확인
    if (number < 0 || number > 9) {
        return; // 유효하지 않은 숫자는 그리지 않음
    }

    // 현재 숫자에 대한 세그먼트 활성화 정보 가져오기
    const _Bool* currentSegments = segments[number];
    int i;
    // 각 세그먼트를 순회하며 그리기
    for (i = 0; i < 7; ++i) {
        // 사용할 색상 결정: 활성화 여부에 따라 activeColor 또는 inactiveColor 사용
        RGB color = currentSegments[i] ? activeColor : inactiveColor;

        // 세그먼트의 상대적 시작점, 끝점 좌표 가져오기 (size=1.0 기준)
        float x1_rel = segCoords[i][0];
        float y1_rel = segCoords[i][1];
        float x2_rel = segCoords[i][2];
        float y2_rel = segCoords[i][3];

        // 크기 및 위치 조절을 적용한 실제 절대 좌표 계산
        float x1_abs = posX + x1_rel * size;
        float y1_abs = posY + y1_rel * size;
        float x2_abs = posX + x2_rel * size;
        float y2_abs = posY + y2_rel * size;

        // 세그먼트의 방향 벡터 계산
        float dx = x2_abs - x1_abs;
        float dy = y2_abs - y1_abs;

        // 벡터 길이 계산
        float length = sqrt(dx * dx + dy * dy);

        // 길이가 너무 짧으면 그리지 않음 (오류 방지)
        if (length < 0.00001f) {
            continue;
        }

        // 정규화된 방향 벡터
        float ndx = dx / length;
        float ndy = dy / length;

        // 정규화된 수직 벡터 (방향 벡터를 90도 회전)
        float pdx = -ndy;
        float pdy = ndx;

        // 끝점을 안쪽으로 당길 거리 설정 (두께에 비례하여 조절, 이 값은 튜닝이 필요할 수 있습니다)
        // 0.15f는 예시 값이며, 숫자의 크기와 두께에 따라 조절해야 합니다.
        // 작게 하면 틈이 좁아지고, 크게 하면 틈이 넓어집니다.
        float retract = thickness * 0.15f;

        // 안쪽으로 당겨진 시작점과 끝점 계산
        float x1_adj = x1_abs + ndx * retract;
        float y1_adj = y1_abs + ndy * retract;
        float x2_adj = x2_abs - ndx * retract;
        float y2_adj = y2_abs - ndy * retract;

        // 사각형의 절반 두께 계산
        float halfThickness = thickness / 2.0f;

        // 사각형의 네 꼭짓점 계산 (안쪽으로 당겨진 시작점/끝점 기준)
        float v1x = x1_adj - halfThickness * pdx;
        float v1y = y1_adj - halfThickness * pdy;
        float v2x = x1_adj + halfThickness * pdx;
        float v2y = y1_adj + halfThickness * pdy;
        float v3x = x2_adj + halfThickness * pdx;
        float v3y = y2_adj + halfThickness * pdy;
        float v4x = x2_adj - halfThickness * pdx;
        float v4y = y2_adj - halfThickness * pdy;

        // 사각형 색상 설정
        glColor3f(color.rgbIn_r, color.rgbIn_g, color.rgbIn_b);

        // 사각형 그리기 (GL_QUADS 사용)
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

    // 길이가 0이면 그리지 않음
    if (dx == 0.0f && dy == 0.0f) {
        return;
    }

    // 선분의 정규화된 방향 벡터와 수직 벡터 계산
    float length = sqrt(dx * dx + dy * dy);
    float ndx = dx / length;
    float ndy = dy / length;
    float pdx = -ndy; // 수직 벡터
    float pdy = ndx;

    // 사각형의 네 꼭짓점 계산
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

// 문자를 중심 (0,0) 기준으로 그리는 함수
void drawCharacter(char c, float height, float thickness, RGB color) {
    float halfHeight = height / 2.0f;
    float charWidth = height * 0.8f; // 문자의 폭 (높이에 비례하여 대략 설정)
    float halfWidth = charWidth / 2.0f;

    // 색상 설정 (RGB 구조체를 사용하는 것으로 가정)
    glColor3f(color.rgbIn_r, color.rgbIn_g, color.rgbIn_b);

    if (c == 'I') {
        // 'I'는 수직선 하나를 (0, -halfHeight)에서 (0, halfHeight)로 그립니다.
        drawSegmentQuad(0, -halfHeight, 0, halfHeight, thickness, color);
    }
    else if (c == 'V') {
        // 'V'는 두 개의 대각선을 (0,0) 기준으로 그립니다.
        // (0,0) 기준: 좌상단 (-halfWidth, halfHeight), 하단 (0, -halfHeight), 우상단 (halfWidth, halfHeight)
        drawSegmentQuad(-halfWidth, halfHeight, 0, -halfHeight, thickness, color); // 좌상단 -> 하단
        drawSegmentQuad(0, -halfHeight, halfWidth, halfHeight, thickness, color); // 하단 -> 우상단
    }
    else if (c == 'X') {
        // 'X'는 교차하는 두 개의 대각선을 (0,0) 기준으로 그립니다.
        // (0,0) 기준: 좌상단 (-halfWidth, halfHeight), 우하단 (halfWidth, -halfHeight)
        // 좌하단 (-halfWidth, -halfHeight), 우상단 (halfWidth, halfHeight)
        drawSegmentQuad(-halfWidth, halfHeight, halfWidth, -halfHeight, thickness, color); // 좌상단 -> 우하단
        drawSegmentQuad(-halfWidth, -halfHeight, halfWidth, halfHeight, thickness, color); // 좌하단 -> 우상단
    }
    // 다른 문자가 필요하다면 여기에 추가
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
    default: return ""; // 1-12가 아닌 경우 빈 문자열 반환
    }
}

float getRomanNumeralWidth(const char* roman, float charHeight) {
    float width = 0;
    float charSpacing = charHeight * 0.1f; // 문자 사이 간격
    float iWidth = charHeight * 0.2f; // 'I'의 폭
    float vxWidth = charHeight * 0.8f; // 'V', 'X'의 폭 (drawCharacter에서 사용한 값)

    int len = 0;
    while (roman[len] != '\0') {
        len++;
    }

    for (int j = 0; j < len; ++j) {
        if (roman[j] == 'I') width += iWidth;
        else if (roman[j] == 'V' || roman[j] == 'X') width += vxWidth;

        if (j < len - 1) width += charSpacing; // 마지막 문자가 아니면 간격 추가
    }
    // 폭 계산을 더 정교하게 하려면 각 문자의 실제 폭을 측정하거나 미리 정의해야 함
    // 여기서는 간단히 문자 수와 대략적인 평균 폭으로 계산 (조금 부정확할 수 있음)
    if (len > 0) {
        // 문자 수 * 대략적인 평균 문자 폭 + (문자 수 - 1) * 간격
        return (float)len * (charHeight * 0.5f) + (float)(len - 1) * charSpacing;
    }
    return 0;
}

// 정수 시간(hour)에 해당하는 로마자 문자열을 특정 위치(centerX, centerY)에
// 시계 방향에 맞춰 회전하여 그리는 함수 (angle 자동 계산)
void drawRomanNumeral(int hour, float centerX, float centerY, float charHeight, float thickness, RGB color) {
    const char* roman = getRomanNumeralString(hour);
    if (roman[0] == '\0' || hour < 1 || hour > 12) return; // 유효하지 않은 시간 또는 범위

    // 시계 각도 계산
    // 12시가 위쪽(0도)이라고 가정하고 시계 방향으로 각도가 증가한다고 생각할 때
    // (혹은 위쪽 0도, 시계 방향으로 음수 각도 증가로 생각할 수도 있습니다. OpenGL의 glRotatef 방향에 따라 조절 필요)
    // 여기서는 12시를 0도로, 1시를 -30도로, 3시를 -90도로 계산하겠습니다.
    // 각 시간 위치는 360도 / 12 = 30도 간격입니다.
    // 시간 12는 0도 또는 360도, 시간 1은 30도, 시간 2는 60도 ... 시간 11은 330도에 해당합니다.
    // 시계 각도는 일반적으로 위쪽(12시)을 0도로 보고 시계 방향으로 증가합니다.
    // OpenGL의 glRotatef는 기본적으로 Z축 양의 방향(화면을 뚫고 나오는 방향)에서 봤을 때
    // 반시계 방향으로 회전하는 것이 양수 각도입니다.
    // 따라서 시계 방향으로 회전시키려면 각도에 -1을 곱하거나, 각도를 360에서 빼주어야 합니다.
    // 여기서는 시계 각도를 계산한 뒤 OpenGL 회전을 위해 음수 각도로 변환하여 사용하겠습니다.

    float angle_degrees;
    if (hour == 12) {
        angle_degrees = 0.0f; // 12시는 위쪽 (0도)
    }
    else {
        // 1시 -> 30도, 2시 -> 60도, ..., 11시 -> 330도
        angle_degrees = (float)hour * 30.0f;
    }

    // OpenGL은 반시계 방향이 양수이므로, 시계 방향 회전을 위해 각도에 -1을 곱합니다.
    float rotation_angle_opengl = -angle_degrees;

    // 이제부터는 이전 코드와 동일하게 로마자 블록 전체를 회전된 로컬 좌표계에서 그립니다.

    float totalWidth = getRomanNumeralWidth(roman, charHeight);
    float charSpacing = charHeight * 0.1f;
    float iWidth = charHeight * 0.2f;
    float vxWidth = charHeight * 0.8f;

    glPushMatrix(); // 현재 변환 행렬 저장

    // 1. 시계의 시간 위치(전체 로마자 블록의 중심이 놓일 위치)로 이동
    glTranslatef(centerX, centerY, 0.0f);

    // 2. 계산된 각도에 맞춰 전체 로마자 블록 회전
    glRotatef(rotation_angle_opengl, 0, 0, 1);

    // 3. 회전된 로컬 좌표계 (X축이 반지름 방향)에서 각 문자를 수평으로 배치할 시작 X 위치 계산
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

        glPushMatrix(); // 현재 (이동 및 회전된) 행렬 저장
        glTranslatef(charCenterX_local, 0, 0); // 로컬 X 위치로 이동

        // 문자를 그립니다. drawCharacter_Local 함수는 (0,0)을 기준으로 그립니다.
        drawCharacter(currentChar, charHeight, thickness, color);

        glPopMatrix(); // 문자를 그린 후 행렬 복원

        currentX_local += currentCharWidth + charSpacing;
    }

    glPopMatrix(); // 전체 로마자 블록 그린 후 처음 행렬 복원
}

// drawCharacter_Local, getRomanNumeralString, getRomanNumeralWidth 함수는 이전과 동일하게 사용합니다.


void drawRomanNumeral2(int hour, float centerX, float centerY, float charHeight, float thickness, RGB color) {
    const char* roman = getRomanNumeralString(hour);
    if (roman[0] == '\0') return; // 유효하지 않은 시간

    // 로마자 전체 문자열의 대략적인 폭 계산
    float totalWidth = getRomanNumeralWidth(roman, charHeight);
    float charSpacing = charHeight * 0.1f; // 문자 사이 간격
    float iWidth = charHeight * 0.2f; // 'I'의 폭
    float vxWidth = charHeight * 0.8f; // 'V', 'X'의 폭

    // 첫 번째 문자의 시작 X 위치 (로마자 블록의 중심 기준)
    float startX = centerX - totalWidth / 2.0f;
    float currentX = startX;

    // 각 문자를 순회하며 그리기
    int len = 0;
    while (roman[len] != '\0') {
        len++;
    }

    for (int j = 0; j < len; ++j) {
        char currentChar = roman[j];
        float currentCharWidth = 0;

        // 현재 문자의 폭 결정
        if (currentChar == 'I') currentCharWidth = iWidth;
        else if (currentChar == 'V' || currentChar == 'X') currentCharWidth = vxWidth;
        else continue; // 지원하지 않는 문자

        // 현재 문자의 중심 X 좌표 계산
        float charCenterX = currentX + currentCharWidth / 2.0f;

        // 문자를 그립니다.
        drawCharacter(currentChar, charHeight, thickness, color);

        // 다음 문자의 시작 X 위치 업데이트
        currentX += currentCharWidth + charSpacing;
    }
}
