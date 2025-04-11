#include <windows.h>
#include <stdio.h>

typedef struct letter
{
    char ch;
    int x;
    int y;
} LETTER;

void gotoxy(int x, int y);
void clickPoint(LETTER* letter, POINT* mousePos, int* isDragging);

int main()
{
    LETTER letterptr = { 'O', 10, 5 }; // ����ü ���� ����
    LETTER* letter = &letterptr; // �����Ϳ� �ּ� �Ҵ�
    POINT mousePos;     // ���콺 ��ġ
    int isDragging = 0;  // �巡�� ���� (0: �巡�� �� �ƴ�, 1: �巡�� ��)

    // �ܼ� ȭ�� �ʱ�ȭ
    system("cls");

    while (1)
    {
        // ȭ�� ����
        system("cls");
        // ���콺 ��ġ ��������
        GetCursorPos(&mousePos);
        int mouseX = mousePos.x / 9;  // �ܼ� ���� ũ�⿡ �°� ����
        int mouseY = mousePos.y / 19; // �ܼ� ���� ũ�⿡ �°� ����
        gotoxy(0, 0);
        printf("���ĺ� '%c'�� ���콺�� �巡���ϼ���.\n", letter->ch);
        printf("�巡�� ���� (0: �巡�� �� �ƴ�, 1: �巡�� ��): %d\n", isDragging);
        printf("���� ���ĺ� '%c'�� ��ġ: (%d, %d)\n", letter->ch, letter->x, letter->y);
        printf("���콺 ��ġ: X=%d, Y=%d\n", mouseX, mouseY);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { mouseX, mouseY });
        printf("<");
        gotoxy(letter->x, letter->y); // ����: y ��ǥ�� ����
        printf("%c", letter->ch);

        // ���콺 Ŭ�� ���� Ȯ��
        clickPoint(letter, &mousePos, &isDragging); // ����: letter �����͸� ���� ����

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

void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

void clickPoint(LETTER* letter, POINT* mousePos, int* isDragging)
{
    int mouseX = mousePos->x / 9;  // �ܼ� ���� ũ�⿡ �°� ����
    int mouseY = mousePos->y / 19; // �ܼ� ���� ũ�⿡ �°� ����

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000)
    {
        // ���콺 Ŭ���� ���� 'O'�� ���� ��ǥ�� ��
        if (mouseX == letter->x && mouseY == letter->y)
        {
            // �巡�� ����
            *isDragging = 1;
        }
        // �巡�� ���� �� ���ĺ� ��ġ ������Ʈ
        if (*isDragging) // ����: �����͸� ���� �� Ȯ��
        {
            letter->x = mouseX;
            letter->y = mouseY;
        }
    }
    else
    {
        // ���콺 ��ư�� �������� �巡�� ����
        *isDragging = 0;
    }
}
