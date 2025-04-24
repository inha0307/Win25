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
    int x;              // 윈도우 시작 포인트 x
    int y;              // 윈도우 시작 포인트 y
    int width;          // 윈도우의 크기 (너비)
    int height;         // 윈도우의 크기 (높이)
    char name[100];     // 윈도우의 이름
    int color;          // 윈도우의 컬러
    int isMax;          // 윈도우의 최대화 여부 (0: 비최대화, 1: 최대화)
    Butten butten[10];
}MyWin;

int getConsoleWidth();
int getConsoleHeight();
void move_cursor(int row, int col);
void DrawWin(MyWin a);
void clean_DrawWin(MyWin a);
#pragma once
