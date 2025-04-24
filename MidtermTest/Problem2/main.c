#include <stdio.h>
#include <Windows.h>

// 커서 이동 함수
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

// 배경 그리기 함수 (파란 배경 + 하단 회색 작업표시줄)
void DrawBGWithTaskbar(int width, int height) {
    int top_margin = 1;
    int bottom_margin = 1;
    int left_margin = 2;
    int right_margin = 2;

    int fill_width = width - left_margin - right_margin;
    int row, col;
    // 파란 배경 영역 그리기
    for (row = top_margin + 1; row <= height - bottom_margin - 1; row++) {
        move_cursor(row, left_margin + 1);

        for (col = 0; col < fill_width; col++) {
            printf("\033[44m \033[0m");  // 파란 배경
        }
    }

    // 작업표시줄 (회색 배경, 1줄)
    int taskbar_row = height -1;  // 마지막 줄

    move_cursor(taskbar_row, left_margin + 1);
    for (col = 0; col < fill_width; col++) {
        printf("\033[47m \033[0m");  // 밝은 회색 배경 (흰색 배경)
    }

    // 커서 위치 조정
    move_cursor(height + 1, 1);
    fflush(stdout);


}


void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color)
{
    int i, j;

    // 배경색을 설정
    printf("\033[%dm", color);
    if (height != 0)
    {
        // 상단 경계선 그리기
        move_cursor(startY, startX);
        for (i = 0; i < width; i++)
        {
            printf("-");
        }

        for (i = 0; i < height - 2; i++)
        {
            move_cursor(startY + 1 + i, startX);
            printf("|");  // 왼쪽 경계선
            for (j = 0; j < width - 2; j++)
            {
                printf(" ");  // 내부 공간
            }
            move_cursor(startY + 1 + i, startX + width - 1);
            printf("|");  // 오른쪽 경계선

        }
        // 하단 경계선 그리기
        move_cursor(startY + height - 1, startX);
        for (i = 0; i < width; i++)
        {
            printf("\033[%dm-\033[0m", color);
        }
        int x = startX + width - 3;
        int y = startY + 1;
        move_cursor(y, x);
        printf("\033[41m\033[37mX\033[0m\033[%dm", color);


        // 윈도우 이름 출력 (제목 표시줄)
        move_cursor(startY + 1, startX + 1);
        printf("\033[90m%s", title); // 흰색 글자 출력

        // 색상 초기화
        printf("\033[0m"); // 기본 색상으로 복원
    }
    else
        return;
}


int main() {
    int width = 80;
    int height = 25;
    int startX = 8;
    int startY = 5;
    int winwidth = 50;
    int winheight = 15;
    const char* title;
    int color = 43;
    int mouseX;
    int mouseY;
    int prevLButtonState = 0;  // 이전 프레임 좌클릭 상태 (0=뗌, 1=눌림)
    int top_margin = 1;
    int bottom_margin = 1;
    int left_margin = 2;
    int right_margin = 2;

    POINT mousePos;     // 마우스 위치
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    DrawBGWithTaskbar(80, 25);
    drawConsoleWindow(startX, startY, winwidth, winheight, "나의 멋진 윈도우", color);


    while (1)
    {
        // 여백 영역 기준으로 좌표 제한(clamping)
        DrawBGWithTaskbar(80, 25);
        drawConsoleWindow(startX, startY, winwidth, winheight, "나의 멋진 윈도우", color);

        GetCursorPos(&mousePos);
        mouseX = mousePos.x / 9;
        mouseY = mousePos.y / 19;
        int minX = left_margin + 1;
        int maxX = width - right_margin;
        int minY = top_margin + 1;
        int maxY = height - bottom_margin;
        if (mouseX < minX) mouseX = minX;
        if (mouseX > maxX) mouseX = maxX;
        if (mouseY < minY) mouseY = minY;
        if (mouseY > maxY) mouseY = maxY;
        move_cursor(mouseY, mouseX);
        printf("\033[44m\033[30m<\033[0m");

        int x = startX + width - 3;
        int y = startY + 1;

        SHORT currLButtonState = (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000) ? 1 : 0;
        if (currLButtonState == 1 && prevLButtonState == 0)
        {

        }
    }

    move_cursor(40, 0);
    return 0;
}
