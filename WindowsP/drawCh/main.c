#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <math.h>
#include <Windows.h>
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


void drawCircle(float r, int seg);
void drawQuadrangle(float width, float heigth);
void drawCircle2(float r, int seg);
void drawQuadrangle(float width, float heigth);
void drawStar(float r, float seg);
void drawEllipse(float rx, float ry, int segments);
void drawCurve(float* A, float* B, float* C);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void drawBezierCurve(float* A, float* B, float* C, int segments);


int main()
{
	// 초기 투영 설정
	int width = 800;
	int height = 600;
	float faceR = 0.05f;
	float faceA = 0.3f;
	float faceB = 0.5f;
	float scalar = 1.0;
	int i;
	float ArmR = 0;
	float moveT = 0.0f;

	if (!glfwInit()) return -1;
	GLFWwindow* window = glfwCreateWindow(width, height, "Circle", NULL, NULL);
	if (!window) { glfwTerminate(); return -1; }


	glfwMakeContextCurrent(window);

	// 콜백 함수 등록
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	framebuffer_size_callback(window, width, height);
	float keyT = 0;
	float ang = 0;
	float ang2 = 0;
	float a[2] = { -0.05f, 0.1f };
	float b[2] = { 0.0f, 0.1f };
	float c[2] = { 0.05f, 0.1f };

	while (!glfwWindowShouldClose(window))
	{
		// 4) 화면 클리어
		glClear(GL_COLOR_BUFFER_BIT);
		float t = (float)glfwGetTime()/100;
		float xPos = sin(t);


		glColor3f(1.0, 1.0, 0);
		drawCircle(0.2, 100);
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			ang -= t;
			ang2 += t;
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			ang += t;
			ang2 -= t;
		}

		glPushMatrix(); //지구
		
		glRotated(ang, 0, 0, 1);
		glTranslatef(0.6, 0, 0);
		glRotated(-ang, 0, 0, 1);
		glRotated(ang2, 0, 0, 1);
		glColor3f(0.0, 0.0, 1);
		drawCircle(0.1, 100);
		glColor3f(0.0, 1.0, 0);
		glTranslatef(0.1, 0, 0);
		drawCircle(0.02, 100);
		glTranslatef(-0.1, 0, 0);
		glRotated(-ang2, 0, 0, 1);

		glPushMatrix(); //달
		glRotated(ang*2, 0, 0, 1);
		glTranslatef(0.2, 0, 0);
		glRotated(-ang*2, 0, 0, 1);
		glRotated(ang2*2, 0, 0, 1);
		glColor3f(0.8, 0.8, 0.8);
		drawCircle(0.05, 100);
		glColor3f(0.0, 1, 0);
		glTranslatef(0.02, 0, 0);
		drawCircle(0.02, 100);
		glPopMatrix();

		glPopMatrix();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// 8) 정리
	glfwTerminate();
	return 0;
}

void drawCircle(float r, int seg)
{
	int i;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);            // 중심
	for (i = 0; i <= seg; i++)
	{
		float ang = 2.0f * PI * i / seg;
		glVertex2f(cosf(ang) * r, sinf(ang) * r);
	}
	glEnd();
}

void drawCircle2(float r, int seg)
{
	int i;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);            // 중심
	for (i = 0; i <= seg; i++)
	{
		float ang = PI * i / seg;
		glVertex2f(cosf(-ang) * r, sinf(-ang) * r);
	}
	glEnd();
}

void drawQuadrangle(float width, float heigth)
{
	glBegin(GL_QUADS);
	float x1 = -width / 2;
	float y1 = heigth / 2;
	float x2 = width / 2;
	float y2 = heigth / 2;
	float x3 = x2;
	float y3 = -heigth / 2;
	float x4 = x1;
	float y4 = y3;
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);

	glEnd();


}

void drawStar(float r, float seg)
{
	int i;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);

	for (int i = 0; i <= seg * 2; ++i)
	{
		float angle = i * 2 * PI / seg + 180;
		float current_r;
		if (i % 2 == 0) {
			current_r = r;
		}
		else {
			current_r = r * 0.3f;
		}
		glVertex2f(current_r * cos(angle), current_r * sin(angle));
	}

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

void drawCurve(float* A, float* B, float* C) {
	glBegin(GL_LINE_STRIP);
	
	glVertex2f(A[0], A[1]);
	glVertex2f(B[0], B[1]);
	glVertex2f(C[0], C[1]);
	glEnd();
}

void drawEllipse(float rx, float ry, int segments)
{
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < segments; i++)
	{
		float theta = 2.0f * PI * (float)i / (float)segments;
		float x = rx * cos(theta);
		float y = ry * sin(theta);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawBezierCurve(float* A, float* B, float* C, int segments) {
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= segments; ++i) {
		float t = (float)i / segments;

		float x = (1 - t) * (1 - t) * A[0] + 2 * (1 - t) * t * B[0] + t * t * C[0];
		float y = (1 - t) * (1 - t) * A[1] + 2 * (1 - t) * t * B[1] + t * t * C[1];

		glVertex2f(x, y);
	}
	glEnd();
}