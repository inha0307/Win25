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
void clickPoint(Windows* win, POINT* mousePos, int* isDragging);

Windows myWindow[2]; //������ â ���� 2��

// ASCII ��Ʈ�� ������ 2���� �迭
char map[HEIGHT_MAP][WIDTH_MAP];

int main(void)
{
    Windows* Window = &myWindow; // �����Ϳ� �ּ� �Ҵ�
    POINT mousePos;     // ���콺 ��ġ
    int isDragging = 0;  // �巡�� ���� (0: �巡�� �� �ƴ�, 1: �巡�� ��)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // �ڵ��� �� ���� ������
    // ������ â 1
    myWindow[0] = (Windows)
    {
     .x = 10,
     .y = 8,
     .width = 20,
     .height = 7,
     .name = "������ ������â.n1",
     .color = "\033[44m"
    };


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

    gotoxy(0, HEIGHT_MAP);

    while (1)
    {
        // ȭ�� ����
        system("cls");
        setBackground();
        // ���콺 ��ġ ��������
        GetCursorPos(&mousePos);
        int mouseX = mousePos.x / 9;  // �ܼ� ���� ũ�⿡ �°� ����
        int mouseY = mousePos.y / 19; // �ܼ� ���� ũ�⿡ �°� ����
        gotoxy(0, 22);
        printf("'%s'�� ���콺�� �巡���ϼ���.\n", Window[0].name);
        printf("�巡�� ���� (0: �巡�� �� �ƴ�, 1: �巡�� ��): %d\n", isDragging);
        printf("���� ���ĺ� '%s'�� ��ġ: (%d, %d)\n", Window[0].name, Window[0].x, Window[0].y);
        printf("���콺 ��ġ: X=%d, Y=%d\n", mouseX, mouseY);

        if (mouseX < 0)
            mouseX = 0;
        if (mouseX >= WIDTH_MAP)
            mouseX = WIDTH_MAP - 1;
        if (mouseY < 0)
            mouseY = 0;
        if (mouseY >= HEIGHT_MAP)
            mouseY = HEIGHT_MAP - 1;
        gotoxy(mouseX, mouseY);
        printf("\033[42m<\033[0m");
        draWindow(&Window[0]);

        // ���콺 Ŭ�� ���� Ȯ��
        clickPoint(&Window[0], &mousePos, &isDragging);

        // ���� ����: ESC Ű�� ������ ���α׷� ����
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            printf("\n���α׷� ����\n");
            break;
        }

        // ��� ��� (CPU ��� ����ȭ)

        Sleep(10);
    }

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
            printf("\033[42m "); // ������ �ʷϻ����� ����
        }
        printf("\n");
    }

    printf("\033[0m"); // ���� �ʱ�ȭ
}

void clickPoint(Windows* win, POINT* mousePos, int* isDragging)
{
    int mouseX = mousePos->x / 9;
    int mouseY = mousePos->y / 19;

    // ���콺 Ŭ�� ���� ��
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000)
    {
        // �巡�װ� ���� ���۵��� �ʾҴٸ�: Ŭ�� ������ ������ ��ǥ �ȿ� ���� ���� ����
        if (*isDragging == 0 &&
            mouseX >= win->x &&
            mouseX <= win->x + win->width &&
            mouseY >= win->y &&
            mouseY <= win->y + win->height)
        {
            *isDragging = 1;
        }

        // �̹� �巡�� ���̶�� ��ǥ ��� ������Ʈ
        if (*isDragging == 1)
        {
            // ���콺 ��ġ ������Ʈ
            win->x = mouseX;
            win->y = mouseY;

            // ����ȭ�� ������ ����� �ʵ��� ����
            if (win->x < 1) win->x = 1;
            if (win->y < 1) win->y = 1;
            if (win->x + win->width >= WIDTH_MAP)
                win->x = WIDTH_MAP - win->width + 1;
            if (win->y + win->height >= HEIGHT_MAP)
                win->y = HEIGHT_MAP - win->height + 1;
        }
    }
    else
    {
        // ���콺 ���� �巡�� ����
        *isDragging = 0;
    }
}
