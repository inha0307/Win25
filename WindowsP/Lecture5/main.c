#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define WIDTH_MAP 120
#define HEIGHT_MAP 22


typedef struct Windows
{
    int x; //Ŀ���� �̵��� x��ǥ
    int y; //Ŀ���� �̵��� x��ǥ
    int width; //������ â ����
    int height; //������ â ����
    char* name; //������ â �̸�
    char* color; //������ â �÷�
} Windows;

void gotoxy(int x, int y); //Ŀ�� �̵� �Լ�
void draWindow(Windows* win); //������ â ���� �Լ�
void setBackground(); //��� �ʱ�ȭ �Լ�

Windows myWindow[2]; //������ â ���� 2��

// ASCII ��Ʈ�� ������ 2���� �迭
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
    // ������ â 1
    myWindow[0] = (Windows)
    {
     .x = 10,
     .y = 3,
     .width = 20,
     .height = 7,
     .name = "������ ������â.n1",
     .color = "\033[44m"
    };
    draWindow(&myWindow[0]);

    // ������ â 2
    myWindow[1] = (Windows)
    {
     .x = 15,
     .y = 5,
     .width = 20,
     .height = 7,
     .name = "������ ������â.n2",
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

    //ù��° ��
    gotoxy(x, y);
    printf("\033[43m+");
    for (i = 0; i < width - 2; i++)
    {
        printf("-");
    }
    printf("+\n");

    //�ι�° ��
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

    //3~6�� ° ��
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

    //������ ��
    gotoxy(x, y + height - 1);
    printf("+");
    for (i = 0; i < width - 2; i++)
    {
        printf("-");
    }
    printf("+\n\033[0m"); // ���� �ʱ�ȭ
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
                printf("\033[30m\033[42m%c\033[0m", map[i][j]); // Ư�� ���ڿ� ���� ������ ���������� ����
            }
            else if (map[i][j] == '^')
            {
                printf("\033[31m\033[42m%c\033[0m", map[i][j]); // Ư�� ���ڿ� ���� ������ ���������� ����
            }
            else
            {
                printf("\033[42m%c\033[0m", map[i][j]); // ������ �ʷϻ����� ����
            }
        }
        printf("\n");
    }

    printf("\033[0m"); // ���� �ʱ�ȭ
}