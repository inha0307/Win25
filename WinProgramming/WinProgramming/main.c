#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "mywin.h"
#include <string.h>

int zOrder[3] = { 0,1,2 };  // â�� �׷����� ����: index�� windows �迭 �ε�����
int click[3] = { 0,0,0 };
int memory_cursor[3];
MyWin windows[3];
int icon[3][2];

void updateCursorColorByWindow(int mouseX, int mouseY , int height, int bottom_margin)
{
    int i, idx;
    int colorSet = 0;

    // �۾�ǥ���� ���� üũ
    if (mouseY >= height - bottom_margin && mouseY < height)
    {
        // �۾�ǥ���� �����̸� ȸ�� ���� ���� (ANSI ���� 47)
        memory_cursor[2] = 47;

        return;
    }

    // zOrder�� 0~2����, 2�� ���� �տ� �ִ� ������
    // �ڿ������� ������ Ž���Ͽ� Ȱ��ȭ�� ������ �� ���콺 ��ǥ ���� ������ ã��
    for (i = 2; i >= 0; i--)
    {
        idx = zOrder[i];

        // Ȱ��ȭ�� ���������� Ȯ��
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
        // Ȱ��ȭ�� �����찡 ���ų� ���콺�� ������ ���� ��� �⺻ ���� ����
        memory_cursor[2] = 44;  // ��: ���� �Ķ���
    }
}




int isMouseInWindow(int mouseX, int mouseY, MyWin* win)
{
    return (mouseX >= win->x && mouseX < win->x + win->width &&
        mouseY >= win->y && mouseY < win->y + win->height);
}

// ����: windows �迭, zOrder �迭, memory_cursor �迭 ���� �� �ʱ�ȭ �Ǿ�����

// �켱������ ���� ���� �������� ������ memory_cursor[2]�� ����


// â�� �� ������ �ø��� �Լ�
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
    POINT mousePos;     // ���콺 ��ġ
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
        printf("�ܼ� ũ�� ������ ������ �� �����ϴ�.\n");
        return 1;
    }

    
    // ���� ���� �Ķ������� ĥ�ϱ�
    for (row = top_margin + 1; row < height - bottom_margin; row++)
    {
        move_cursor(row, left_margin + 1);

        // ���� ���� �ʺ�

        for (col = 0; col < fill_width; col++)
        {
            printf("\033[44m \033[0m");
        }
    }
    // �۾� ǥ����
    for (row = height - bottom_margin; row < height; row++)
    {
        move_cursor(row, left_margin + 1);

        // ���� ���� �ʺ�
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
    int prevLButtonState = 0;  // ���� ������ ��Ŭ�� ���� (0=��, 1=����)
    
    int inDex = 0;
    int i, j;

    

    while (1)
    {
        // ���� ���� �������� ��ǥ ����(clamping)
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

        //���콺 Ŀ�� �̵� �� �� ��ȯ
        move_cursor(memory_cursor[1], memory_cursor[0]);
        printf("\033[%dm \033[0m", memory_cursor[2]);  // ���� ��ǥ�� ����� ���� ���

        // ���� ���콺 ��ǥ�� ���� ����
        memory_cursor[0] = mouseX;
        memory_cursor[1] = mouseY;

        // ���콺 ��ư ���¿� ���� ���� ���� (��: Ŭ�� �� ������ 31, �ƴϸ� ��� 32)
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

        //������
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
                        // â ����
                        click[idx] = 1;
                        bringWindowToFront(idx);
                        DrawWin(windows[idx]);
                    }
                    else
                    {
                        // â �ݱ�
                        for (row = windows[idx].y; row < windows[idx].y + windows[idx].height; row++)
                        {
                            move_cursor(row, windows[idx].x);
                            for (col = windows[idx].x; col < windows[idx].x + windows[idx].width; col++)
                            {
                                printf("\033[44m \033[0m");
                            }
                        }
                        click[idx] = 0;

                        // Ȱ��ȭ�� â �ٽ� �׸���
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
        
        //������â ������ ���� ��ư
        if (currLButtonState == 1 && prevLButtonState == 0)
        {
            for (i = 0; i < 3; i++)
            {
                int closeBtnX = windows[i].x + windows[i].width - 11;
                int closeBtnY = windows[i].y + 1;

                if ((mouseX == closeBtnX) && (mouseY == closeBtnY) && click[i] == 1)
                {
                    // â ���� ��ü ����� (�Ķ� ���)
                    for (row = windows[i].y; row < windows[i].y + windows[i].height; row++)
                    {
                        move_cursor(row, windows[i].x);
                        for (col = windows[i].x; col < windows[i].x + windows[i].width; col++)
                        {
                            printf("\033[44m \033[0m");
                        }
                    }

                    click[i] = 0; // ������ ��Ȱ��ȭ

                    // Ȱ��ȭ�� �ٸ� â �ٽ� �׸���
                    for (j = 0; j < 3; j++)
                    {
                        int widx = zOrder[j];
                        if (click[widx] == 1)
                            DrawWin(windows[widx]);
                    }

                    break; // �ѹ��� �� â�� �����Ƿ� �ݺ� ����
                }
            }
        }

        //������â ���� ���� ��� ��ư
        if (currLButtonState == 1 && prevLButtonState == 0)
            {
                // ��� ��ư ���� Ŭ�� Ȯ�� (windows[0] ����)
                
                if ((mouseY == windows[0].y + 1) && (mouseX == windows[0].x + windows[0].width - 8))
                {
                    windows[0].x = 10; 
                    windows[0].y = 5; 
                    windows[0].width = 30; 
                    windows[0].height = 10; 
                    strcpy(windows[0].name, "windows1"); 
                    windows[0].color = 45; 
                    windows[0].isMax = 0;

                    // â �����
                    for (row = top_margin + 1; row < height - bottom_margin; row++)
                    {
                        move_cursor(row, left_margin + 1);

                        // ���� ���� �ʺ�
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
       

                    // �ʿ��ϸ� �ٸ� â �ٽ� �׸��� �Ǵ� ȭ�� ���� ó�� �߰�
                }

                if ((mouseY == windows[1].y + 1) && (mouseX == windows[1].x + windows[1].width - 8))
                {
                    windows[1].x = 12; windows[1].y = 7; windows[1].width = 30; windows[1].height = 10; strcpy(windows[1].name, "windows2"); windows[1].color = 46; windows[1].isMax = 0;
                    
                    // â �����
                    for (row = top_margin + 1; row < height - bottom_margin; row++)
                    {
                        move_cursor(row, left_margin + 1);

                        // ���� ���� �ʺ�
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


                    // �ʿ��ϸ� �ٸ� â �ٽ� �׸��� �Ǵ� ȭ�� ���� ó�� �߰�
                }

                if ((mouseY == windows[2].y + 1) && (mouseX == windows[2].x + windows[2].width - 8))
                {
                    windows[2].x = 14; windows[2].y = 9; windows[2].width = 30; windows[2].height = 10; strcpy(windows[2].name, "windows3"); windows[2].color = 40; windows[2].isMax = 0;

                    // â �����
                    for (row = top_margin + 1; row < height - bottom_margin; row++)
                    {
                        move_cursor(row, left_margin + 1);

                        // ���� ���� �ʺ�
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

        //������â Ȯ�� �ʷ� ��ư
        if (currLButtonState == 1 && prevLButtonState == 0)
            {
                // ��� ��ư ���� Ŭ�� Ȯ�� (windows[0] ����)

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
            for (i = 2; i >= 0; i--)  // zOrder �ڿ������� ������ (�� ������)
            {
                int widx = zOrder[i];

                if (click[widx] == 1 &&
                    mouseX >= windows[widx].x && mouseX < windows[widx].x + windows[widx].width &&
                    mouseY >= windows[widx].y && mouseY < windows[widx].y + windows[widx].height)
                {
                    // Ŭ���� �����츦 �� ������ �ø�
                    bringWindowToFront(widx);

                    // ��� Ȱ��ȭ�� �����츦 zOrder ������� �ٽ� �׸�
                    for (j = 0; j < 3; j++)
                    {
                        int drawIdx = zOrder[j];
                        if (click[drawIdx] == 1)
                            DrawWin(windows[drawIdx]);
                    }
                    break;  // �� ���� �� â�� ó��
                }
            }
        }

        if (mouseY >= height - bottom_margin && mouseY < height)
        {
            // ������ 3�� �׸��� ����
            int idx;
            for (idx = 0; idx < 3; idx++)
            {
                int iconX = icon[idx][1];
                int iconY = icon[idx][0];

                move_cursor(iconY, iconX);

                if (click[idx] == 1)
                {
                    // Ȱ��ȭ�� â: ����� ���
                    printf("\033[45m");
                }
                else
                {
                    // ��Ȱ��ȭ�� â: ȸ�� ���
                    printf("\033[47m");
                }

                printf("\033[32mo");  // ������ �ڸ� ���� ���� ���

                printf("\033[0m");  // ���� �ʱ�ȭ
            }


        }

        prevLButtonState = currLButtonState; // ���� ����
    }
    

    

   


    // Ŀ�� ��ġ�� ���� �Ʒ������� �̵�(���û���)
    move_cursor(height, 1);
    return 0;
}

