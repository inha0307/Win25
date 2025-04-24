#include <stdio.h>

// Ŀ�� �̵� �Լ�
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

// ��� �׸��� �Լ� (�Ķ� ��� + �ϴ� ȸ�� �۾�ǥ����)
void DrawBGWithTaskbar(int width, int height) {
    int top_margin = 1;
    int bottom_margin = 1;
    int left_margin = 2;
    int right_margin = 2;

    int fill_width = width - left_margin - right_margin;
    int row, col;
    // �Ķ� ��� ���� �׸���
    for (row = top_margin + 1; row <= height - bottom_margin - 1; row++) {
        move_cursor(row, left_margin + 1);

        for (col = 0; col < fill_width; col++) {
            printf("\033[44m \033[0m");  // �Ķ� ���
        }
    }

    // �۾�ǥ���� (ȸ�� ���, 1��)
    int taskbar_row = height -1;  // ������ ��

    move_cursor(taskbar_row, left_margin + 1);
    for (col = 0; col < fill_width; col++) {
        printf("\033[47m \033[0m");  // ���� ȸ�� ��� (��� ���)
    }

    // Ŀ�� ��ġ ����
    move_cursor(height + 1, 1);
    fflush(stdout);


}


void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color)
{
    int i, j;

    // ������ ����
    printf("\033[%dm", color);
    if (height != 0)
    {
        // ��� ��輱 �׸���
        move_cursor(startY, startX);
        for (i = 0; i < width; i++)
        {
            printf("-");
        }

        for (i = 0; i < height - 2; i++)
        {
            move_cursor(startY + 1 + i, startX);
            printf("|");  // ���� ��輱
            for (j = 0; j < width - 2; j++)
            {
                printf(" ");  // ���� ����
            }
            move_cursor(startY + 1 + i, startX + width - 1);
            printf("|");  // ������ ��輱

        }
        // �ϴ� ��輱 �׸���
        move_cursor(startY + height - 1, startX);
        for (i = 0; i < width; i++)
        {
            printf("\033[%dm-\033[0m", color);
        }
        int x = startX + width - 3;
        int y = startY + 1;
        move_cursor(y, x);
        printf("\033[41m\033[37mX\033[0m\033[%dm", color);


        // ������ �̸� ��� (���� ǥ����)
        move_cursor(startY + 1, startX + 1);
        printf("\033[90m%s", title); // ��� ���� ���

        // ���� �ʱ�ȭ
        printf("\033[0m"); // �⺻ �������� ����
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

    DrawBGWithTaskbar(80, 25);
    drawConsoleWindow(startX, startY, winwidth, winheight, "���� ���� ������", color);


    move_cursor(40, 0);
    return 0;
}
