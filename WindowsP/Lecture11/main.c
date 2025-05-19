#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <math.h>
#include <windows.h> // Sleep 함수를 사용하기 위해 추가합니다.

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1000, 1000, "GLFW: Rotating Triangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    float angle_degrees = 0.0f; // 회전 각도를 저장할 변수 (도)
    const float PI = 3.14159265358979323846f;

    while (!glfwWindowShouldClose(window)) {
        // 각도를 라디안으로 변환
        float angle_radians = angle_degrees * (PI / 180.0f);

        glClear(GL_COLOR_BUFFER_BIT); // 화면 지우기

        glBegin(GL_TRIANGLES); // 삼각형 그리기 시작

        // 첫 번째 꼭짓점 (0.0, 1.0) 회전
        glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
        glVertex2f(
            0.0f * cos(angle_radians) - 1.0f * sin(angle_radians),
            0.0f * sin(angle_radians) + 1.0f * cos(angle_radians)
        );

        // 두 번째 꼭짓점 (-0.866, -0.5) 회전
        glColor3f(0.0f, 1.0f, 0.0f); // 초록색
        glVertex2f(
            -0.866f * cos(angle_radians) - (-0.5f) * sin(angle_radians),
            -0.866f * sin(angle_radians) + (-0.5f) * cos(angle_radians)
        );

        // 세 번째 꼭짓점 (0.866, -0.5) 회전
        glColor3f(0.0f, 0.0f, 1.0f); // 파란색
        glVertex2f(
            0.866f * cos(angle_radians) - (-0.5f) * sin(angle_radians),
            0.866f * sin(angle_radians) + (-0.5f) * cos(angle_radians)
        );


        glEnd(); // 삼각형 그리기 끝

        // 다음 프레임을 위해 각도 증가 (예: 1도씩 증가)
        angle_degrees += 1.0f;


        Sleep(10); // 회전 속도 조절 (100ms 대기 -> 10ms 대기로 변경하여 더 부드러운 회전)

        glfwSwapBuffers(window); // 버퍼 교체하여 화면에 표시
        glfwPollEvents(); // 이벤트 처리
    }

    glfwDestroyWindow(window); // 창 파괴
    glfwTerminate(); // GLFW 종료
    return 0;
}
