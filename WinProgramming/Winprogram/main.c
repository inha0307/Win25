#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "mywin.h"
#include <string.h>

int memory_cursor[3];


void updateCursorColorByWindow(int mouseX, int mouseY, int height, int bottom_margin, MyWin* windows, int winrogo_click);

int main()
{
    POINT mousePos;     // ���콺 ��ġ
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
        printf("�ܼ� ũ�� ������ ������ �� �����ϴ�.\n");
        return 1;
    }


    // ���� ���� �Ķ������� ĥ�ϱ�
    for (row = top_margin + 1; row < height - bottom_margin; row++)
    {
        move_cursor(row, left_margin + 1);

        // ���� ���� �ʺ�

        for (col = 0; col < fill_width; col++)
        {
            printf("\033[44m \033[0m");
        }
    }
    // �۾� ǥ����
    for (row = height - bottom_margin; row < height; row++)
    {
        move_cursor(row, left_margin + 1);

        // ���� ���� �ʺ�
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

        //���콺 Ŀ�� �̵� �� �� ��ȯ
        move_cursor(memory_cursor[1], memory_cursor[0]);
        printf("\033[%dm \033[0m", memory_cursor[2]);  // ���� ��ǥ�� ����� ���� ���

        // ���� ���콺 ��ǥ�� ���� ����
        memory_cursor[0] = mouseX;
        memory_cursor[1] = mouseY;

        // ���콺 ��ư ���¿� ���� ���� ���� (��: Ŭ�� �� ������ 31, �ƴϸ� ��� 32)
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

        if (currLButtonState == 1 && prevLButtonState == 0) // ��ư ���� ���� ����
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

        // ���� ���¸� ���� ���·� ���� (�߿�!)
        prevLButtonState = currLButtonState;

    }
    return 0;
}

void updateCursorColorByWindow(int mouseX, int mouseY, int height, int bottom_margin, MyWin* windows, int winrogo_click)
{
    int i, idx;
    int colorSet = 0;

    // �۾�ǥ���� ���� üũ
    if (mouseY >= height - bottom_margin && mouseY < height)
    {
        // �۾�ǥ���� �����̸� ȸ�� ���� ���� (ANSI ���� 47)
        memory_cursor[2] = 47;

        return;
    }

    // zOrder�� 0~2����, 2�� ���� �տ� �ִ� ������
    // �ڿ������� ������ Ž���Ͽ� Ȱ��ȭ�� ������ �� ���콺 ��ǥ ���� ������ ã��
    
            if (mouseX >= windows->x && mouseX < windows->x + windows->width &&
                mouseY >= windows->y && mouseY < windows->y + windows->height && winrogo_click == 1)
            {
                memory_cursor[2] = windows->color;
                colorSet = 1;
            }

    if(!colorSet)
    {
        // Ȱ��ȭ�� �����찡 ���ų� ���콺�� ������ ���� ��� �⺻ ���� ����
        memory_cursor[2] = 44;  // ��: ���� �Ķ���
    }
}