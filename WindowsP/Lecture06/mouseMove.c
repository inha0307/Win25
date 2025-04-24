#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define WIDTH_MAP 120
#define HEIGHT_MAP 22

POINT dragOffset = { 0,0 };

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
void clickPoint(Windows* win, POINT* mousePos, int* isDragging, POINT* dragOffset);

Windows myWindow[2]; //윈도우 창 갯수 2개

// ASCII 아트를 저장할 2차원 배열
char map[HEIGHT_MAP][WIDTH_MAP];

int main(void)
{
    Windows* Window = &myWindow; // 포인터에 주소 할당
    POINT mousePos;     // 마우스 위치
    int isDragging = 0;  // 드래그 상태 (0: 드래그 중 아님, 1: 드래그 중)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 핸들을 한 번만 가져옴
    // 윈도우 창 1
    myWindow[0] = (Windows)
    {
     .x = 10,
     .y = 8,
     .width = 20,
     .height = 7,
     .name = "최인하 윈도우창.n1",
     .color = "\033[44m"
    };


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

    gotoxy(0, HEIGHT_MAP);

    while (1)
    {
        // 화면 갱신
        system("cls");
        setBackground();
        // 마우스 위치 가져오기
        GetCursorPos(&mousePos);
        int mouseX = mousePos.x / 9;  // 콘솔 문자 크기에 맞게 조정
        int mouseY = mousePos.y / 19; // 콘솔 문자 크기에 맞게 조정
        gotoxy(0, 22);
        printf("'%s'을 마우스로 드래그하세요.\n", Window[0].name);
        printf("드래그 상태 (0: 드래그 중 아님, 1: 드래그 중): %d\n", isDragging);
        printf("현재 알파벳 '%s'의 위치: (%d, %d)\n", Window[0].name, Window[0].x, Window[0].y);
        printf("마우스 위치: X=%d, Y=%d\n", mouseX, mouseY);

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

        // 마우스 클릭 상태 확인
        clickPoint(&Window[0], &mousePos, &isDragging, &dragOffset);

        // 종료 조건: ESC 키를 누르면 프로그램 종료
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            printf("\n프로그램 종료\n");
            break;
        }

        // 잠시 대기 (CPU 사용 최적화)

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
            printf("\033[42m "); // 배경색을 초록색으로 설정
        }
        printf("\n");
    }

    printf("\033[0m"); // 색상 초기화
}

void clickPoint(Windows* win, POINT* mousePos, int* isDragging, POINT* dragOffset)
{
    int mouseX = mousePos->x / 9;
    int mouseY = mousePos->y / 19;

    // 마우스 클릭 중일 때
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000)
    {
        if (*isDragging == 0)
        {
            // 클릭 지점이 윈도우 좌표 안에 있을 때만 드래그 시작
            if (mouseX >= win->x &&
                mouseX <= win->x + win->width &&
                mouseY >= win->y &&
                mouseY <= win->y + win->height)
            {
                *isDragging = 1;

                // 드래그 시작 시점에 마우스와 윈도우 좌상단 간 오프셋 저장
                dragOffset->x = mouseX - win->x;
                dragOffset->y = mouseY - win->y;
            }
        }
        else if (*isDragging == 1)
        {
            // 오프셋을 고려해 윈도우 위치 계산
            int newX = mouseX - dragOffset->x;
            int newY = mouseY - dragOffset->y;

            // 바탕화면 범위를 벗어나지 않도록 보정
            if (newX < 1) newX = 1;
            if (newY < 1) newY = 1;
            if (newX + win->width >= WIDTH_MAP)
                newX = WIDTH_MAP - win->width + 1;
            if (newY + win->height >= HEIGHT_MAP)
                newY = HEIGHT_MAP - win->height + 1;

            // 윈도우 위치 업데이트
            win->x = newX;
            win->y = newY;
        }
    }
    else
    {
        // 마우스 떼면 드래그 종료
        *isDragging = 0;
    }
}

