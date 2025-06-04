#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#define PI 3.1415926535f

//GL_POINTS	점들을 그립니다.
//GL_LINES	선분들을 그립니다. (2개씩 묶어서 선으로 처리)
//GL_LINE_STRIP	선들을 연결하여 하나의 꺾은 선으로 그립니다.
//GL_LINE_LOOP	선들을 연결하고, 마지막 점에서 첫 점까지 선을 추가합니다.
//GL_TRIANGLES	삼각형들을 그립니다. (3개씩 묶어서 삼각형으로 처리)
//GL_TRIANGLE_STRIP	연속된 삼각형 띠를 그립니다.
//GL_TRIANGLE_FAN	삼각형 부채꼴을 그립니다.
//GL_QUADS	사각형들을 그립니다. (4개씩 묶어서) (OpenGL 3.1 이후로는 deprecated)
//GL_QUAD_STRIP	쌍으로 된 사각형 띠를 그립니다. (OpenGL 3.1 이후로는 deprecated)
//GL_POLYGON	하나의 다각형을 그립니다. (OpenGL 3.1 이후로는 deprecated)
// 
// 원 그리기: 반지름 r, 세그먼트 수 seg

void drawCircle(float r, int seg) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);            // 중심
    for (int i = 0; i <= seg; ++i) {
        float a = 2.0f * PI * i / seg;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();
}

// 스마일맨 얼굴(눈 + 입) 그리기
void drawFace(float eyeR, float eyeOffsetX, float eyeOffsetY, GLFWwindow* window) {
    // 왼쪽 눈
    glPushMatrix();
    glTranslatef(-eyeOffsetX, eyeOffsetY, 0.0f);
    drawCircle(eyeR, 16);
    glPopMatrix();

    // 오른쪽 눈
    glPushMatrix();
    glTranslatef(eyeOffsetX, eyeOffsetY, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.03, 0);
        glVertex2f(0.0, -0.01);
        glVertex2f(0.03, 0);
        glEnd();
        
    }
    else
    {
        drawCircle(eyeR, 16);
    }
    
    glPopMatrix();

    // 웃는 입 (반원 아크)
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 20; ++i) {
        // -30° .. -150° 사이
        float a = (-30.0f - 120.0f * i / 20.0f) * (PI / 180.0f);
        glVertex2f(cosf(a) * 0.5f * eyeOffsetX, sinf(a) * 0.5f * eyeOffsetY);
    }
    glEnd();
}

// 육망성(별) 그리기: 반지름 r
void drawHexagram(float r) {
    float h = r * 0.866f; // sqrt(3)/2 * r
    glBegin(GL_TRIANGLES);
    // 윗 삼각형
    glVertex2f(0.0f, r);
    glVertex2f(-h, -r * 0.5f);
    glVertex2f(h, -r * 0.5f);
    // 아랫 삼각형 (역방향)
    glVertex2f(0.0f, -r);
    glVertex2f(-h, r * 0.5f);
    glVertex2f(h, r * 0.5f);
    glEnd();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // 뷰포트 설정: 창 전체 크기에 맞게 설정
    glViewport(0, 0, width, height);

    // 투영 행렬 설정: 종횡비 유지
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 종횡비 계산
    float aspect_ratio = (float)width / (float)height;

    // 창의 종횡비에 맞춰 직교 투영 영역 설정
    if (width > height) {
        // 너비가 높이보다 큰 경우: 좌우 영역 확장
        glOrtho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -1.0, 1.0);
    }
    else {
        // 높이가 너비보다 크거나 같은 경우: 상하 영역 확장
        glOrtho(-1.0, 1.0, -1.0 / aspect_ratio, 1.0 / aspect_ratio, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

 

int main(void) {
    // 1) GLFW 초기화
    if (!glfwInit()) return -1;

    // 2) 윈도우 생성 & 컨텍스트 바인딩
    GLFWwindow* window = glfwCreateWindow(800, 600, "Smiley Orbit & Hexagram", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    // 프레임버퍼 크기 변경 콜백 함수 등록
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 초기 뷰포트 및 투영 설정 (콜백 함수를 한 번 호출하여 초기 설정)
    framebuffer_size_callback(window, 800, 600);

    // 3) 2D 직교 투영 설정 (좌표계 -1..1)
    glOrtho(-1, 1, -1, 1, -1, 1);

    // 애니메이션 파라미터
    const float smileOrbitR = 0.6f;   // 스마일맨 공전 반경
    const float smileRadius = 0.15f;  // 스마일맨 얼굴 반경
    const float eyeR = 0.02f;         // 눈 반경
    const float eyeOffX = 0.05f,
        eyeOffY = 0.07f;      // 눈 위치 오프셋
    const float hexOrbitR = 0.3f;     // 육망성 공전 반경
    const float hexRadius = 0.07f;    // 육망성 크기

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        float t = (float)glfwGetTime();

        // 공전/자전 각도 계산
        float smileOrbitAng = t * 20.0f;     // 스마일맨 공전 속도
        float hexOrbitAng = t * 60.0f;     // 별 공전 속도 (빠름)
        float hexSelfAng = t * 200.0f;    // 별 자체 자전 속도 (더 빠름)

        // 4) 화면 클리어
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);
        drawCircle(2, 100);

        // 5) 스마일맨 공전 궤도
        glPushMatrix();
        glRotatef(smileOrbitAng, 0, 0, 1);                // 중심 기준 공전
        glTranslatef(smileOrbitR, 0.0f, 0.0f);          // 궤도 반경만큼 이동

        // 얼굴 그리기
        glColor3f(1.0f, 1.0f, 0.0f);                    // 노랑 얼굴
        drawCircle(smileRadius, 64);

        // 얼굴 특징(눈/입)은 역회전으로 수평 유지
        glPushMatrix();
        glRotatef(-smileOrbitAng, 0, 0, 1);
        glColor3f(0.0f, 0.0f, 0.0f);                  // 눈/입 검정
        drawFace(eyeR, eyeOffX, eyeOffY, window);
        glPopMatrix();

        // 6) 육망성 공전 & 자전
        glPushMatrix();
        glRotatef(hexOrbitAng, 0, 0, 1);                // 스마일맨 기준 공전
        glTranslatef(hexOrbitR, 0.0f, 0.0f);          // 궤도 반경만큼 이동
        glRotatef(hexSelfAng, 0, 0, 1);                 // 별 자체 자전
        glColor3f(0.2f, 0.6f, 1.0f);                  // 파랑 별
        drawHexagram(hexRadius);
        glPopMatrix();

        glPopMatrix();  // 스마일맨 공전 행렬 복원

        // 7) 버퍼 스왑 & 이벤트 처리
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 8) 정리
    glfwTerminate();
    return 0;
}