#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define WIDTH_MAP 120
#define HEIGHT_MAP 22


typedef struct Windows
{
    int x; //커서가 이동할 x좌표
    int y; //커서가 이동할 x좌표
    int width; //윈도우 창 길이
    int height; //윈도우 창 높이
    char* name; //윈도우 창 이름
    char* color; //윈도우 창 컬러
} Windows;

void gotoxy(int x, int y); //커서 이동 함수
void draWindow(Windows* win); //윈도우 창 제작 함수
void setBackground(); //배경 초기화 함수

Windows myWindow[2]; //윈도우 창 갯수 2개

// ASCII 아트를 저장할 2차원 배열
char map[HEIGHT_MAP][WIDTH_MAP + 20] = {
    "+----------------------------------------------------------------------------------------------------------+",
    "|  /\\_/\\        / \\__/ \\      / \\     / \\      / \\__/ \\      / \\__/ \\      / \\     / \\      / \\__/ \\       |",
    "| ( o.o )      (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )      |",
    "|  > ^ <        > ^ <        > ^ <     > ^ <     > ^ <        > ^ <     > ^ <     > ^ <        > ^ <       |",
    "|                                                                                                          |",
    "|  /\\_/\\        / \\__/ \\      / \\     / \\      / \\__/ \\      / \\__/ \\      / \\     / \\      / \\__/ \\       |",
    "| ( o.o )      (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )      |",
    "|  > ^ <        > ^ <        > ^ <     > ^ <     > ^ <        > ^ <     > ^ <     > ^ <        > ^ <       |",
    "|                                                                                                          |",
    "|  /\\_/\\        / \\__/ \\      / \\     / \\      / \\__/ \\      / \\__/ \\      / \\     / \\      / \\__/ \\       |",
    "| ( o.o )      (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )      |",
    "|  > ^ <        > ^ <        > ^ <     > ^ <     > ^ <        > ^ <     > ^ <     > ^ <        > ^ <       |",
    "|                                                                                                          |",
    "|  /\\_/\\        / \\__/ \\      / \\     / \\      / \\__/ \\      / \\__/ \\      / \\     / \\      / \\__/ \\       |",
    "| ( o.o )      (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )      |",
    "|  > ^ <        > ^ <        > ^ <     > ^ <     > ^ <        > ^ <     > ^ <     > ^ <        > ^ <       |",
    "|                                                                                                          |",
    "|  /\\_/\\        / \\__/ \\      / \\     / \\      / \\__/ \\      / \\__/ \\      / \\     / \\      / \\__/ \        |",
    "| ( o.o )      (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )   ( o.o )   (  o o  )    ( o.o )      |",
    "|  > ^ <        > ^ <        > ^ <     > ^ <     > ^ <        > ^ <     > ^ <     > ^ <        > ^ <       |",
    "|                                                                                                          |",
    "+----------------------------------------------------------------------------------------------------------+"
};


int main(void)
{
    setBackground();
    // 윈도우 창 1
    myWindow[0] = (Windows)
    {
     .x = 10,
     .y = 3,
     .width = 20,
     .height = 7,
     .name = "최인하 윈도우창.n1",
     .color = "\033[44m"
    };
    draWindow(&myWindow[0]);

    // 윈도우 창 2
    myWindow[1] = (Windows)
    {
     .x = 15,
     .y = 5,
     .width = 20,
     .height = 7,
     .name = "최인하 윈도우창.n2",
     .color = "\033[45m"
    };
    draWindow(&myWindow[1]);
    gotoxy(0, HEIGHT_MAP);
    return 0;
}

void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    HANDLE WConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(WConsole, pos);
}

void draWindow(Windows* win)
{
    int i, j;
    int x = win->x - 1;
    int y = win->y - 1;
    int width = win->width;
    int height = win->height;
    char* str = win->name;
    char* cl = win->color;

    //첫번째 줄
    gotoxy(x, y);
    printf("\033[43m+");
    for (i = 0; i < width - 2; i++)
    {
        printf("-");
    }
    printf("+\n");

    //두번째 줄
    gotoxy(x, y + 1);
    printf("|");
    for (i = 0; i < width - 2; i++)
    {
        printf("%s ", cl);
    }
    gotoxy(x + 1, y + 1);
    printf("%s", str);
    gotoxy(x + width - 1, y + 1);
    printf("\033[43m|");

    //3~6번 째 줄
    gotoxy(x, y + 2);
    printf("+");
    for (i = 0; i < width - 2; i++)
    {
        printf("-");
    }
    printf("+\n");

    for (i = 0; i < height - 4; i++)
    {
        gotoxy(x, y + i + 3);
        printf("|");
        for (j = 0; j < width - 2; j++)
        {
            printf("%s ", cl);
        }

        printf("\033[43m|\n");
    }

    //마지막 줄
    gotoxy(x, y + height - 1);
    printf("+");
    for (i = 0; i < width - 2; i++)
    {
        printf("-");
    }
    printf("+\n\033[0m"); // 색상 초기화
}
void setBackground()
{
    int i, j;
    for (i = 0; i < HEIGHT_MAP; i++)
    {
        for (j = 0; j < WIDTH_MAP; j++)
        {


            if (map[i][j] == '/' || map[i][j] == '\\' || map[i][j] == 'o')
            {
                printf("\033[30m\033[42m%c\033[0m", map[i][j]); // 특정 문자에 대해 배경색을 빨간색으로 설정
            }
            else if (map[i][j] == '^')
            {
                printf("\033[31m\033[42m%c\033[0m", map[i][j]); // 특정 문자에 대해 배경색을 빨간색으로 설정
            }
            else
            {
                printf("\033[42m%c\033[0m", map[i][j]); // 배경색을 초록색으로 설정
            }
        }
        printf("\n");
    }

    printf("\033[0m"); // 색상 초기화
}