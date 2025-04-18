#include <stdio.h>
#include <Windows.h>
#include "mywin.h"

// �ܼ� �ʺ� (�÷� ��)�� ���ϴ� �Լ�
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;  // ���� ��
}

// �ܼ� ���� (�� ��)�� ���ϴ� �Լ�
int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
    {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;  // ���� ��
}

// Ŀ�� �̵� �Լ�: \033[row;colH
void move_cursor(int row, int col)
{
    printf("\033[%d;%dH", row, col);
}

void DrawWin(MyWin a)
{
    int i, j;

    // ������ ����
    printf("\033[%dm", a.color);
    if (a.height != 0)
    {
        // ��� ��輱 �׸���
        move_cursor(a.y, a.x);
        for (i = 0; i < a.width; i++)
        {
            printf("-");
        }

        for (i = 0; i < a.height - 2; i++)
        {
            move_cursor(a.y + 1 + i, a.x);
            printf("|");  // ���� ��輱
            for (j = 0; j < a.width - 2; j++)
            {
                printf(" ");  // ���� ����
            }
            move_cursor(a.y + 1 + i, a.x + a.width - 1);
            printf("|");  // ������ ��輱
        }

        // ���� ǥ���� ��ư�� �׸��� (��: 3��)
        for (i = 0; i < 3; i++)
        {
            a.butten[i].x = a.x + a.width - 11 + i * 3;
            a.butten[i].y = a.y + 1;
            move_cursor(a.y + 1, a.x + a.width - 11 + i * 3);
            printf("\033[%dm��\033[0m\033[%dm", a.butten[i].color[1], a.color);
        }

        // �ϴ� ��輱 �׸���
        move_cursor(a.y + a.height - 1, a.x);
        for (i = 0; i < a.width; i++)
        {
            printf("\033[%dm-\033[0m", a.color);
        }

        // ������ �̸� ��� (���� ǥ����)
        move_cursor(a.y + 1, a.x + 1);
        printf("\033[%dm%s", a.color, a.name); // ��� ���� ���

        // ���� �ʱ�ȭ
        printf("\033[0m"); // �⺻ �������� ����
    }
    else
        return;
}

