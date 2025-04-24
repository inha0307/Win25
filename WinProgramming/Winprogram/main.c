#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "mywin.h"
#include <string.h>

int memory_cursor[3];


void updateCursorColorByWindow(int mouseX, int mouseY, int height, int bottom_margin, MyWin* windows, int winrogo_click);

int main()
{
    POINT mousePos;     // 마우스 위치
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int dragWinIdx = -1;
    int isDragging = 0;
    int width = getConsoleWidth();
    int height = getConsoleHeight();

    int left_margin = 5;
    int right_margin = 5;
    int top_margin = 1;
    int bottom_margin = 3;
    int row, col;
    int fill_width = width - left_margin - right_margin;
    int mouseX;
    int mouseY;
    int prevLButtonState = 0;
    

    MyWin window;
    window.x = 0;
    window.y = 0;
    window.width = 5;
    window.height = 10;
    window.color = 41;


    if (width == -1 || height == -1) {
        printf("콘솔 크기 정보를 가져올 수 없습니다.\n");
        return 1;
    }


    // 내부 영역 파란색으로 칠하기
    for (row = top_margin + 1; row < height - bottom_margin; row++)
    {
        move_cursor(row, left_margin + 1);

        // 내부 영역 너비

        for (col = 0; col < fill_width; col++)
        {
            printf("\033[44m \033[0m");
        }
    }
    // 작업 표시줄
    for (row = height - bottom_margin; row < height; row++)
    {
        move_cursor(row, left_margin + 1);

        // 내부 영역 너비
        int fill_width = width - left_margin - right_margin;

        for (col = 0; col < fill_width; col++)
        {
            printf("\033[47m \033[0m");
        }
    }
    window.x = 6;
    window.y = 17;
	
    move_cursor(28, 8);
    printf("\033[32m\033[47m&\033[0m");

    int winrogo_click = 0;
    while(1)
    {
        GetCursorPos(&mousePos);
        mouseX = mousePos.x / 9;
        mouseY = mousePos.y / 19;

        int minX = left_margin + 1;
        int maxX = width - right_margin;
        int minY = top_margin + 1;
        int maxY = height - bottom_margin + 2;
        if (mouseX < minX) mouseX = minX;
        if (mouseX > maxX) mouseX = maxX;
        if (mouseY < minY) mouseY = minY;
        if (mouseY > maxY) mouseY = maxY;

        //마우스 커서 이동 및 색 변환
        move_cursor(memory_cursor[1], memory_cursor[0]);
        printf("\033[%dm \033[0m", memory_cursor[2]);  // 이전 좌표에 저장된 색상 출력

        // 현재 마우스 좌표에 색상값 저장
        memory_cursor[0] = mouseX;
        memory_cursor[1] = mouseY;

        // 마우스 버튼 상태에 따라 색상 결정 (예: 클릭 시 빨간색 31, 아니면 녹색 32)
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000)
        {
            updateCursorColorByWindow(mouseX, mouseY, height, bottom_margin, &window, winrogo_click);
            move_cursor(mouseY, mouseX);
            printf("\033[%dm\033[33m+\033[0m", memory_cursor[2]);
        }
        else
        {
            updateCursorColorByWindow(mouseX, mouseY, height, bottom_margin, &window, winrogo_click);
            move_cursor(mouseY, mouseX);
            printf("\033[%dm\033[30m+\033[0m", memory_cursor[2]);
        }

        SHORT currLButtonState = ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000)) ? 1 : 0;

        if (currLButtonState == 1 && prevLButtonState == 0) // 버튼 눌림 순간 감지
        {
            if (mouseX == 8 && mouseY == 28 && winrogo_click == 0)
            {
                move_cursor(28, 8);
                printf("\033[42m\033[33m&\033[0m");
                DrawWin(window);
                winrogo_click = 1;
            }
            else if (mouseX == 8 && mouseY == 28 && winrogo_click != 0)
            {
                move_cursor(28, 8);
                printf("\033[32m\033[47m&\033[0m");
                clean_DrawWin(window);
                winrogo_click = 0;
            }
        }

        if (winrogo_click == 1)
        {
            move_cursor(28, 8);
            printf("\033[42m\033[33m&\033[0m");
        }
        else
        {
            move_cursor(28, 8);
            printf("\033[32m\033[47m&\033[0m");
        }

        // 현재 상태를 이전 상태로 저장 (중요!)
        prevLButtonState = currLButtonState;

    }
    return 0;
}

void updateCursorColorByWindow(int mouseX, int mouseY, int height, int bottom_margin, MyWin* windows, int winrogo_click)
{
    int i, idx;
    int colorSet = 0;

    // 작업표시줄 영역 체크
    if (mouseY >= height - bottom_margin && mouseY < height)
    {
        // 작업표시줄 영역이면 회색 배경색 지정 (ANSI 배경색 47)
        memory_cursor[2] = 47;

        return;
    }

    // zOrder는 0~2까지, 2가 가장 앞에 있는 윈도우
    // 뒤에서부터 앞으로 탐색하여 활성화된 윈도우 중 마우스 좌표 포함 윈도우 찾기
    
            if (mouseX >= windows->x && mouseX < windows->x + windows->width &&
                mouseY >= windows->y && mouseY < windows->y + windows->height && winrogo_click == 1)
            {
                memory_cursor[2] = windows->color;
                colorSet = 1;
            }

    if(!colorSet)
    {
        // 활성화된 윈도우가 없거나 마우스가 윈도우 밖인 경우 기본 색상 지정
        memory_cursor[2] = 44;  // 예: 배경색 파란색
    }
}