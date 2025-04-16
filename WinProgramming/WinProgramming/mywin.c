#include <stdio.h>
#include <Windows.h>
#include "mywin.h"

// 콘솔 너비 (컬럼 수)를 구하는 함수
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return -1;  // 실패 시
}

// 콘솔 높이 (줄 수)를 구하는 함수
int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return -1;  // 실패 시
}

// 커서 이동 함수: \033[row;colH
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void DrawWin(MyWin a) {
    int i,j;

    // 배경색을 회색으로 설정 (초록, 파랑 제외)
    printf("\033[%dm", a.color); // 회색 배경
    if (a.height != 0)
    {
        // 상단 경계선 그리기
        move_cursor(a.y, a.x);
        for (i = 0; i < a.width; i++)
        {
            printf("-");
        }

        for (i = 0; i < a.height - 2; i++)
        {
            move_cursor(a.y + 1 + i, a.x);
            printf("|");  // 왼쪽 경계선
            for (j = 0; j < a.width - 2; j++)
            {
                printf(" ");  // 내부 공간
            }
            move_cursor(a.y + 1 + i, a.x + a.width - 1);
            printf("|");  // 오른쪽 경계선
        }


        // 제목 표시줄
        move_cursor(a.y + 1, a.x + a.width - 11);
        printf("\033[%dm\033[31m●\033[%dm  \033[%dm\033[33m●\033[%dm  \033[%dm\033[32m●\033[%dm", a.color, a.color, a.color, a.color); // 제목 표시줄 버튼

        // 하단 경계선 그리기
        move_cursor(a.y + a.height - 1, a.x);
        for (i = 0; i < a.width; i++)
        {
            printf("\033[%dm-", a.color);
        }

        // 윈도우 이름 출력 (제목 표시줄)
        move_cursor(a.y + 1, a.x + 1);
        printf("%s", a.name); // 흰색 글자 출력

        // 색상 초기화
        printf("\033[0m"); // 기본 색상으로 복원
    }
    else
        return 0;
    
}