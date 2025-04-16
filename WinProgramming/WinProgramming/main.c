#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "mywin.h"
#include <string.h>

void clearBackground(int startRow, int startCol, int fillWidth, int fillHeight) 
{
    int i, j;
    for (i = startRow; i < startRow + fillHeight-3; i++) 
    {
        move_cursor(i, startCol);
        for (j = 0; j < fillWidth-3; j++)
        {
            printf("\033[44m \033[0m");
        }
       
    }
    //�۾� ������
    for (i = startRow + fillHeight - 3; i < startRow + fillHeight; i++)
    {
        move_cursor(i, startCol);
        for (j = 0; j < fillWidth - 3; j++)
        {
            printf("\033[47m \033[0m");
        }
    }
}

void drawIcon(int x, int y) {
    move_cursor(y, x);
    printf("\033[46m��\033[0m"); // �������� �׸��ϴ�.
}

MyWin windows[3]; // ����ü �迭 3��
int memory_Width[3], memory_Height[3], memory_X[3], memory_Y[3];

void ProcessWindowButtons(int idx, int mouseX, int mouseY, int width, int height, int* isVisible) 
{
    MyWin* win = &windows[idx];
    memory_Width[idx] = win->width;
    memory_Height[idx] = win->height;
    memory_X[idx] = win->x;
    memory_Y[idx] = win->y;


    if (mouseX == win->x + win->width - 11 && mouseY == win->y + 1) 
    {
        win->height = 0;
        clearBackground(2, 6, width - 10, height - 7);
        DrawWin(*win);

    }
    else if (mouseX == win->x + win->width - 8 && mouseY == win->y + 1)
    {
        win->width = memory_Width[idx];
        win->height = memory_Height[idx];
        win->x = memory_X[idx];
        win->y = memory_Y[idx];

        memory_Width[idx] = win->width;
        memory_Height[idx] = win->height;
        memory_X[idx] = win->x;
        memory_Y[idx] = win->y;

        clearBackground(2, 6, width - 10, height - 7);
        DrawWin(*win);

    }
    else if (mouseX == win->x + win->width - 5 && mouseY == win->y + 1) 
    {
        win->width = width - 13;
        win->height = height - 10;
        win->x = 6;
        win->y = 2;

        memory_Width[idx] = win->width;
        memory_Height[idx] = win->height;
        memory_X[idx] = win->x;
        memory_Y[idx] = win->y;

        clearBackground(2, 6, width - 10, height - 7);
        DrawWin(*win);

    }
    else if (mouseX == width - 100 && mouseY == height - 7) 
    {
        *isVisible = 1;
        clearBackground(2, 6, width - 10, height - 7);

        win->width = memory_Width[idx];
        win->height = memory_Height[idx];
        win->x = memory_X[idx];
        win->y = memory_Y[idx];
        DrawWin(*win);

    }
}


int main()
{
    int width = getConsoleWidth();
    int height = getConsoleHeight();
    int isVisible = 1; // ������ ǥ�� ����
    POINT mousePos;     // ���콺 ��ġ
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (width == -1 || height == -1) {
        printf("�ܼ� ũ�⸦ �������� �� �����߽��ϴ�.\n");
        return 1;
    }


    int startRow = 2; // ���� ����
    int startCol = 6; // ���� ����
    int fillWidth = width - 7; // ������ ���� 5ĭ
    int fillHeight = height - 4; // �Ʒ��� ���� 3ĭ

    // ���� ����� ���ÿ� �ʱ�ȭ�� �Ұ����� ��Ȳ�̶��,
    windows[0].x = 10;
    windows[0].y = 5;
    windows[0].width = 30;
    windows[0].height = 10;
    strcpy(windows[0].name, "������ 1");
    windows[0].color = 45;
    windows[0].isMax = 0;

    windows[1].x = 12;
    windows[1].y = 7;
    windows[1].width = 30;
    windows[1].height = 10;
    strcpy(windows[1].name, "������ 2");
    windows[1].color = 46;
    windows[1].isMax = 0;

    windows[2].x = 14;
    windows[2].y = 9;
    windows[2].width = 30;
    windows[2].height = 10;
    strcpy(windows[2].name, "������ 3");
    windows[2].color = 47;
    windows[2].isMax = 0;


    clearBackground(2, 6, width - 10, height - 7);
    if (isVisible) 
    {
        DrawWin(windows[0]);
        DrawWin(windows[1]);
        DrawWin(windows[2]);
    }
    drawIcon(width - 100, height - 7); // �۾� �����ٿ� ������ �׸���

    memory_Width[0] = windows[0].width;
    memory_Height[0] = windows[0].height;
    memory_X[0] = windows[0].x;
    memory_Y[0] = windows[0].y;

    memory_Width[1] = windows[1].width;
    memory_Height[1] = windows[1].height;
    memory_X[1] = windows[1].x;
    memory_Y[1] = windows[1].y;

    memory_Width[2] = windows[2].width;
    memory_Height[2] = windows[2].height;
    memory_X[2] = windows[2].x;
    memory_Y[2] = windows[2].y;

    while (1)
    {
        move_cursor(height - 3, 0);

        GetCursorPos(&mousePos);
        int mouseX = mousePos.x / 9;
        int mouseY = mousePos.y / 19;
        int isDragging = 0;

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            isDragging = 1;
            move_cursor(mouseY, mouseX);
            printf("\033[44m\033[33m+\033[0m");

            // ��: ù ��° ������(0�� �ε���) ��ư ó��
            ProcessWindowButtons(0, mouseX, mouseY, width, height, &isVisible);
           
            // �ʿ�� 1, 2�� �ε����� ȣ�� ����
            ProcessWindowButtons(1, mouseX, mouseY, width, height, &isVisible);
            ProcessWindowButtons(2, mouseX, mouseY, width, height, &isVisible);
        }
        else
        {
            move_cursor(mouseY, mouseX);
            printf("\033[44m\033[30m+\033[0m");
            isDragging = 0;
        }

        drawIcon(width - 100, height - 7);

        move_cursor(mouseY + 1, mouseX);
        printf("\033[44m\033[30m@~(^_^ )~!\033[0m");
        Sleep(100);
        move_cursor(mouseY + 1, mouseX);
        printf("\033[44m\033[30m!~ (^_^)~@\033[0m");
        Sleep(100);
    }

    return 0;
}
