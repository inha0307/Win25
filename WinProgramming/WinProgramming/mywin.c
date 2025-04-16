#include <stdio.h>
#include <Windows.h>
#include "mywin.h"

// �ܼ� �ʺ� (�÷� ��)�� ���ϴ� �Լ�
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;  // ���� ��
}

// �ܼ� ���� (�� ��)�� ���ϴ� �Լ�
int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;  // ���� ��
}

// Ŀ�� �̵� �Լ�: \033[row;colH
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void DrawWin(MyWin a) {
    int i,j;

    // ������ ȸ������ ���� (�ʷ�, �Ķ� ����)
    printf("\033[%dm", a.color); // ȸ�� ���
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


        // ���� ǥ����
        move_cursor(a.y + 1, a.x + a.width - 11);
        printf("\033[%dm\033[31m��\033[%dm  \033[%dm\033[33m��\033[%dm  \033[%dm\033[32m��\033[%dm", a.color, a.color, a.color, a.color); // ���� ǥ���� ��ư

        // �ϴ� ��輱 �׸���
        move_cursor(a.y + a.height - 1, a.x);
        for (i = 0; i < a.width; i++)
        {
            printf("\033[%dm-", a.color);
        }

        // ������ �̸� ��� (���� ǥ����)
        move_cursor(a.y + 1, a.x + 1);
        printf("%s", a.name); // ��� ���� ���

        // ���� �ʱ�ȭ
        printf("\033[0m"); // �⺻ �������� ����
    }
    else
        return 0;
    
}