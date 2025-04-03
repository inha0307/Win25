#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y);
void draWindow(int width, int high);

int main(void)
{
    int width, high;
    char str[100];
    puts("가로 길이와 세로 길이를 입력하시오.");
    scanf("%d %d", &width, &high);
    draWindow(width, high);
    printf("커서를 이동할 곳의 좌표를 쓰세요.\n가로: %d\n세로: %d\n", width, high);
    scanf("%d %d", &width, &high);
    gotoxy(width, high-1);
    scanf("%s", str);
    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    HANDLE WConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(WConsole, pos);
}

void draWindow(int width, int high)
{
    int i;
    system("cls");
    gotoxy(0, 0);
    printf("+");
    for (i = 0; i < width; i++) 
    {
        printf("-");
    }
    printf("+\n");
    gotoxy(0, 2);
    for (i = 0; i < width+1; i++) 
    {
        printf("-");
    }
    for (i = 0; i < high; i++) 
    {
        gotoxy(0, i + 1);
        printf("|");
        gotoxy(width + 1, i + 1);
        printf("|\n");
    }

    gotoxy(0, high + 1);
    printf("+");
    for (i = 0; i < width; i++) 
    {
        printf("-");
    }
    printf("+\n");
}
