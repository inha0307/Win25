#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "mywin.h"
#include <string.h>

int zOrder[3] = { 0,1,2 };  // 창의 그려지는 순서: index가 windows 배열 인덱스임
int click[3] = { 0,0,0 };
int memory_cursor[3];
MyWin windows[3];
int icon[3][2];

void updateCursorColorByWindow(int mouseX, int mouseY , int height, int bottom_margin)
{
    int i, idx;
    int colorSet = 0;

    // 작업표시줄 영역 체크
    if (mouseY >= height - bottom_margin && mouseY < height)
    {
        // 작업표시줄 영역이면 회색 배경색 지정 (ANSI 배경색 47)
        memory_cursor[2] = 47;

        return;
    }

    // zOrder는 0~2까지, 2가 가장 앞에 있는 윈도우
    // 뒤에서부터 앞으로 탐색하여 활성화된 윈도우 중 마우스 좌표 포함 윈도우 찾기
    for (i = 2; i >= 0; i--)
    {
        idx = zOrder[i];

        // 활성화된 윈도우인지 확인
        if (click[idx] == 1)
        {
            if (mouseX >= windows[idx].x && mouseX < windows[idx].x + windows[idx].width &&
                mouseY >= windows[idx].y && mouseY < windows[idx].y + windows[idx].height)
            {
                memory_cursor[2] = windows[idx].color;
                colorSet = 1;
                break;
            }
        }
    }

    if (!colorSet)
    {
        // 활성화된 윈도우가 없거나 마우스가 윈도우 밖인 경우 기본 색상 지정
        memory_cursor[2] = 44;  // 예: 배경색 파란색
    }
}




int isMouseInWindow(int mouseX, int mouseY, MyWin* win)
{
    return (mouseX >= win->x && mouseX < win->x + win->width &&
        mouseY >= win->y && mouseY < win->y + win->height);
}

// 가정: windows 배열, zOrder 배열, memory_cursor 배열 선언 및 초기화 되어있음

// 우선순위가 가장 높은 윈도우의 색상값을 memory_cursor[2]에 저장


// 창을 맨 앞으로 올리는 함수
void bringWindowToFront(int idx)
{
    int pos = -1;
    int i;
    for (i = 0; i < 3; i++)
    {
        if (zOrder[i] == idx)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1) return;

    for (i = pos; i < 2; i++)
        zOrder[i] = zOrder[i + 1];
    zOrder[2] = idx;
}

int main()
{
    POINT mousePos;     // 마우스 위치
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int width = getConsoleWidth();
    int height = getConsoleHeight();

    int left_margin = 5;
    int right_margin = 5;
    int top_margin = 1;
    int bottom_margin = 3;
    int row, col;
    int fill_width = width - left_margin - right_margin;

   

    if (width == -1 || height == -1) {
        printf("콘솔 크기 정보를 가져올 수 없습니다.\n");
        return 1;
    }

    
    // 내부 영역 파란색으로 칠하기
    for (row = top_margin + 1; row < height - bottom_margin; row++)
    {
        move_cursor(row, left_margin + 1);

        // 내부 영역 너비

        for (col = 0; col < fill_width; col++)
        {
            printf("\033[44m \033[0m");
        }
    }
    // 작업 표시줄
    for (row = height - bottom_margin; row < height; row++)
    {
        move_cursor(row, left_margin + 1);

        // 내부 영역 너비
        int fill_width = width - left_margin - right_margin;

        for (col = 0; col < fill_width; col++)
        {
            printf("\033[47m \033[0m");
        }
    }
    
    int icon[3][2];
   
    icon[0][0] = height - bottom_margin + 1;  icon[0][1] = 10;
    icon[1][0] = height - bottom_margin + 1;  icon[1][1] = 20;
    icon[2][0] = height - bottom_margin + 1;  icon[2][1] = 30;


    windows[0].x = 10; windows[0].y = 5; windows[0].width = 30; windows[0].height = 10; 
    strcpy(windows[0].name, "windows1"); windows[0].color = 45; windows[0].isMax = 0;
    windows[0].butten[0].color[0] = 44; windows[0].butten[0].color[1] = 31;
    windows[0].butten[1].color[0] = 44; windows[0].butten[1].color[1] = 33;
    windows[0].butten[2].color[0] = 44; windows[0].butten[2].color[1] = 32;

    windows[1].x = 12; windows[1].y = 7; windows[1].width = 30; windows[1].height = 10; strcpy(windows[1].name, "windows2"); windows[1].color = 46; windows[1].isMax = 0;
    windows[1].butten[0].color[0] = 44; windows[1].butten[0].color[1] = 31;
    windows[1].butten[1].color[0] = 44; windows[1].butten[1].color[1] = 33;
    windows[1].butten[2].color[0] = 44; windows[1].butten[2].color[1] = 32;
    
    windows[2].x = 14; windows[2].y = 9; windows[2].width = 30; windows[2].height = 10; strcpy(windows[2].name, "windows3"); windows[2].color = 40; windows[2].isMax = 0;
    windows[2].butten[0].color[0] = 44; windows[2].butten[0].color[1] = 31;
    windows[2].butten[1].color[0] = 44; windows[2].butten[1].color[1] = 33;
    windows[2].butten[2].color[0] = 44; windows[2].butten[2].color[1] = 32;
    /*
     DrawWin(windows[0]);
    DrawWin(windows[1]);
    DrawWin(windows[2]);
    */


    move_cursor(icon[0][0], icon[0][1]);
    printf("\033[45mo\033[0m");
    move_cursor(icon[1][0], icon[1][1]);
    printf("\033[45mo\033[0m");
    move_cursor(icon[2][0], icon[2][1]);
    printf("\033[45mo\033[0m");


    GetCursorPos(&mousePos);
    int mouseX;
    int mouseY;
    int prevLButtonState = 0;  // 이전 프레임 좌클릭 상태 (0=뗌, 1=눌림)
    
    int inDex = 0;
    int i, j;

    

    while (1)
    {
        // 여백 영역 기준으로 좌표 제한(clamping)
        GetCursorPos(&mousePos);
        mouseX = mousePos.x / 9;
        mouseY = mousePos.y / 19;
        int minX = left_margin + 1;
        int maxX = width - right_margin;
        int minY = top_margin + 1;
        int maxY = height - bottom_margin + 2;
        if (mouseX < minX) mouseX = minX;
        if (mouseX > maxX) mouseX = maxX;
        if (mouseY < minY) mouseY = minY;
        if (mouseY > maxY) mouseY = maxY;

        //마우스 커서 이동 및 색 변환
        move_cursor(memory_cursor[1], memory_cursor[0]);
        printf("\033[%dm \033[0m", memory_cursor[2]);  // 이전 좌표에 저장된 색상 출력

        // 현재 마우스 좌표에 색상값 저장
        memory_cursor[0] = mouseX;
        memory_cursor[1] = mouseY;

        // 마우스 버튼 상태에 따라 색상 결정 (예: 클릭 시 빨간색 31, 아니면 녹색 32)
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            updateCursorColorByWindow(mouseX, mouseY, height, bottom_margin);
            move_cursor(mouseY, mouseX);
            printf("\033[%dm\033[33m+\033[0m", memory_cursor[2]);
        }
        else
        {
            updateCursorColorByWindow(mouseX, mouseY, height, bottom_margin);
            move_cursor(mouseY, mouseX);
            printf("\033[%dm\033[30m+\033[0m", memory_cursor[2]);
        }

        //아이콘
        SHORT currLButtonState = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? 1 : 0;
        if (currLButtonState == 1 && prevLButtonState == 0)
        {
            for (int idx = 0; idx < 3; idx++)
            {
                int iconX = icon[idx][1];
                int iconY = icon[idx][0];

                if (mouseX == iconX && mouseY == iconY)
                {
                    if (click[idx] == 0)
                    {
                        // 창 열기
                        click[idx] = 1;
                        bringWindowToFront(idx);
                        DrawWin(windows[idx]);
                    }
                    else
                    {
                        // 창 닫기
                        for (row = windows[idx].y; row < windows[idx].y + windows[idx].height; row++)
                        {
                            move_cursor(row, windows[idx].x);
                            for (col = windows[idx].x; col < windows[idx].x + windows[idx].width; col++)
                            {
                                printf("\033[44m \033[0m");
                            }
                        }
                        click[idx] = 0;

                        // 활성화된 창 다시 그리기
                        for (j = 0; j < 3; j++)
                        {
                            int widx = zOrder[j];
                            if (click[widx] == 1)
                                DrawWin(windows[widx]);
                        }
                    }

                    break;
                }
            }
        }
        
        //윈도우창 내리기 빨간 버튼
        if (currLButtonState == 1 && prevLButtonState == 0)
        {
            for (i = 0; i < 3; i++)
            {
                int closeBtnX = windows[i].x + windows[i].width - 11;
                int closeBtnY = windows[i].y + 1;

                if ((mouseX == closeBtnX) && (mouseY == closeBtnY) && click[i] == 1)
                {
                    // 창 영역 전체 지우기 (파란 배경)
                    for (row = windows[i].y; row < windows[i].y + windows[i].height; row++)
                    {
                        move_cursor(row, windows[i].x);
                        for (col = windows[i].x; col < windows[i].x + windows[i].width; col++)
                        {
                            printf("\033[44m \033[0m");
                        }
                    }

                    click[i] = 0; // 윈도우 비활성화

                    // 활성화된 다른 창 다시 그리기
                    for (j = 0; j < 3; j++)
                    {
                        int widx = zOrder[j];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }

                    break; // 한번에 한 창만 닫으므로 반복 종료
                }
            }
        }

        //윈도우창 원래 상태 노란 버튼
        if (currLButtonState == 1 && prevLButtonState == 0)
            {
                // 노란 버튼 영역 클릭 확인 (windows[0] 기준)
                
                if ((mouseY == windows[0].y + 1) && (mouseX == windows[0].x + windows[0].width - 8))
                {
                    windows[0].x = 10; 
                    windows[0].y = 5; 
                    windows[0].width = 30; 
                    windows[0].height = 10; 
                    strcpy(windows[0].name, "windows1"); 
                    windows[0].color = 45; 
                    windows[0].isMax = 0;

                    // 창 지우기
                    for (row = top_margin + 1; row < height - bottom_margin; row++)
                    {
                        move_cursor(row, left_margin + 1);

                        // 내부 영역 너비
                        int fill_width = width - left_margin - right_margin;

                        for (col = 0; col < fill_width; col++)
                        {
                            printf("\033[44m \033[0m");
                        }
                    }
                    for (i = 0; i < 3; i++)
                    {
                        int widx = zOrder[i];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }
       

                    // 필요하면 다른 창 다시 그리기 또는 화면 갱신 처리 추가
                }

                if ((mouseY == windows[1].y + 1) && (mouseX == windows[1].x + windows[1].width - 8))
                {
                    windows[1].x = 12; windows[1].y = 7; windows[1].width = 30; windows[1].height = 10; strcpy(windows[1].name, "windows2"); windows[1].color = 46; windows[1].isMax = 0;
                    
                    // 창 지우기
                    for (row = top_margin + 1; row < height - bottom_margin; row++)
                    {
                        move_cursor(row, left_margin + 1);

                        // 내부 영역 너비
                        int fill_width = width - left_margin - right_margin;

                        for (col = 0; col < fill_width; col++)
                        {
                            printf("\033[44m \033[0m");
                        }
                    }
                    for (i = 0; i < 3; i++)
                    {
                        int widx = zOrder[i];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }


                    // 필요하면 다른 창 다시 그리기 또는 화면 갱신 처리 추가
                }

                if ((mouseY == windows[2].y + 1) && (mouseX == windows[2].x + windows[2].width - 8))
                {
                    windows[2].x = 14; windows[2].y = 9; windows[2].width = 30; windows[2].height = 10; strcpy(windows[2].name, "windows3"); windows[2].color = 40; windows[2].isMax = 0;

                    // 창 지우기
                    for (row = top_margin + 1; row < height - bottom_margin; row++)
                    {
                        move_cursor(row, left_margin + 1);

                        // 내부 영역 너비
                        int fill_width = width - left_margin - right_margin;

                        for (col = 0; col < fill_width; col++)
                        {
                            printf("\033[44m \033[0m");
                        }
                    }
                    for (i = 0; i < 3; i++)
                    {
                        int widx = zOrder[i];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }
                }
               
            }

        //윈도우창 확대 초록 버튼
        if (currLButtonState == 1 && prevLButtonState == 0)
            {
                // 노란 버튼 영역 클릭 확인 (windows[0] 기준)

                if ((mouseY == windows[0].y + 1) && (mouseX == windows[0].x + windows[0].width - 5))
                {
                    windows[0].x = left_margin + 1; windows[0].y = row = top_margin + 1; windows[0].width = fill_width;
                    windows[0].height = height - bottom_margin - 2; strcpy(windows[0].name, "windows1"); windows[0].color = 45; windows[0].isMax = 0;
                    for (i = 0; i < 3; i++)
                    {
                        int widx = zOrder[i];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }
                }
                if ((mouseY == windows[1].y + 1) && (mouseX == windows[1].x + windows[1].width - 5))
                {
                    windows[1].x = left_margin + 1; windows[1].y = row = top_margin + 1; windows[1].width = fill_width;
                    windows[1].height = height - bottom_margin - 2; strcpy(windows[1].name, "windows2"); windows[1].color = 46; windows[1].isMax = 0;
                    for (i = 0; i < 3; i++)
                    {
                        int widx = zOrder[i];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }
                }
                if ((mouseY == windows[2].y + 1) && (mouseX == windows[2].x + windows[2].width - 5))
                {
                    windows[2].x = left_margin + 1; windows[2].y = row = top_margin + 1; windows[2].width = fill_width;
                    windows[2].height = height - bottom_margin - 2; strcpy(windows[2].name, "windows3"); windows[2].color = 40; windows[2].isMax = 0;
                    for (i = 0; i < 3; i++)
                    {
                        int widx = zOrder[i];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }
                }
               
            }
        
        if (currLButtonState == 1 && prevLButtonState == 0)
        {
            for (i = 2; i >= 0; i--)  // zOrder 뒤에서부터 앞으로 (맨 위부터)
            {
                int widx = zOrder[i];

                if (click[widx] == 1 &&
                    mouseX >= windows[widx].x && mouseX < windows[widx].x + windows[widx].width &&
                    mouseY >= windows[widx].y && mouseY < windows[widx].y + windows[widx].height)
                {
                    // 클릭한 윈도우를 맨 앞으로 올림
                    bringWindowToFront(widx);

                    // 모든 활성화된 윈도우를 zOrder 순서대로 다시 그림
                    for (j = 0; j < 3; j++)
                    {
                        int drawIdx = zOrder[j];
                        if (click[drawIdx] == 1)
                            DrawWin(windows[drawIdx]);
                    }
                    break;  // 한 번에 한 창만 처리
                }
            }
        }

        if (mouseY >= height - bottom_margin && mouseY < height)
        {
            // 아이콘 3개 그리기 예시
            int idx;
            for (idx = 0; idx < 3; idx++)
            {
                int iconX = icon[idx][1];
                int iconY = icon[idx][0];

                move_cursor(iconY, iconX);

                if (click[idx] == 1)
                {
                    // 활성화된 창: 보라색 배경
                    printf("\033[45m");
                }
                else
                {
                    // 비활성화된 창: 회색 배경
                    printf("\033[47m");
                }

                printf("\033[32mo");  // 아이콘 자리 공백 문자 출력

                printf("\033[0m");  // 색상 초기화
            }


        }

        prevLButtonState = currLButtonState; // 상태 갱신
    }
    

    

   


    // 커서 위치를 여백 아래쪽으로 이동(선택사항)
    move_cursor(height, 1);
    return 0;
}

