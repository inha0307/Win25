typedef struct Butten
{
    int x;
    int y;
    int width;
    int height;
    int color[2];

}Butten;


typedef struct Win
{
    int x;              // ������ ���� ����Ʈ x
    int y;              // ������ ���� ����Ʈ y
    int width;          // �������� ũ�� (�ʺ�)
    int height;         // �������� ũ�� (����)
    char name[100];     // �������� �̸�
    int color;          // �������� �÷�
    int isMax;          // �������� �ִ�ȭ ���� (0: ���ִ�ȭ, 1: �ִ�ȭ)
    Butten butten[10];
}MyWin;

int getConsoleWidth();
int getConsoleHeight();
void move_cursor(int row, int col);
void DrawWin(MyWin a);
void clean_DrawWin(MyWin a);
#pragma once
