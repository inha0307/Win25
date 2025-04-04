#include <stdio.h>
#include <Windows.h>

typedef struct Windows
{
    int x;
    int y;
    int width;
    int height;
    char* name;
    char* color;
} Windows;

void gotoxy(int x, int y);
void draWindow(const Windows* win);
void setBackground();

int main(void)
{
    Windows myWindow[2];
    myWindow[0].x = 10;
    myWindow[0].y = 3;
    myWindow[0].width = 20;
    myWindow[0].height = 7;
    myWindow[0].name = "최인하 윈도우창.n1";
    myWindow[0].color = "\033[44m";
    setBackground();
    draWindow(&myWindow[0]);
    myWindow[1].x = 15;
    myWindow[1].y = 5;
    myWindow[1].width = 20;
    myWindow[1].height = 7;
    myWindow[1].name = "최인하 윈도우창.n2";
    myWindow[1].color = "\033[45m";
    draWindow(&myWindow[1]);

    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    HANDLE WConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(WConsole, pos);
}

void draWindow(const Windows* win)
{
    int i, j;
    int x = win->x;
    int y = win->y - 1;
    int width = win->width;
    int height = win->height;
    const char* str = win->name;
    const char* cl = win->color;


    gotoxy(x, y);
    printf("\033[43m+");
    for (i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("+\n");

    gotoxy(x, y + 1);
    printf("|");
    for (i = 0; i < width; i++)
    {
        printf("%s ", cl);
    }
    gotoxy(x + 1, y + 1);
    printf("%s", str); 
    gotoxy(x + width + 1, y + 1);
    printf("\033[43m|");

    gotoxy(x, y + 2);
    printf("+");
    for (i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("+\n");

    for (i = 0; i < height; i++)
    {
        gotoxy(x, y + i + 3);
        printf("|");
        for (j = 0; j < width; j++)
        {
            printf("%s ", cl);
        }

        printf("\033[43m|\n");
    }

    gotoxy(x, y + height + 3);
    printf("+");
    for (i = 0; i < width; i++)
    {
        printf("-");
    }
    printf("+\n\033[0m"); // 색상 초기화
}

void setBackground()
{
    int i, j;
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 120; j++)
        {
            printf("\033[42m "); // 빈 공간 출력
        }
        printf("\n");
    }
    printf("\033[0m"); // 색상 초기화
}