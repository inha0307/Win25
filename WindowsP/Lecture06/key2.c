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
    LETTER letterptr = { 'O', 10, 5 }; // 구조체 변수 생성
    LETTER* letter = &letterptr; // 포인터에 주소 할당
    POINT mousePos;     // 마우스 위치
    int isDragging = 0;  // 드래그 상태 (0: 드래그 중 아님, 1: 드래그 중)

    // 콘솔 화면 초기화
    system("cls");

    while (1)
    {
        // 화면 갱신
        system("cls");
        // 마우스 위치 가져오기
        GetCursorPos(&mousePos);
        int mouseX = mousePos.x / 9;  // 콘솔 문자 크기에 맞게 조정
        int mouseY = mousePos.y / 19; // 콘솔 문자 크기에 맞게 조정
        gotoxy(0, 0);
        printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter->ch);
        printf("드래그 상태 (0: 드래그 중 아님, 1: 드래그 중): %d\n", isDragging);
        printf("현재 알파벳 '%c'의 위치: (%d, %d)\n", letter->ch, letter->x, letter->y);
        printf("마우스 위치: X=%d, Y=%d\n", mouseX, mouseY);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { mouseX, mouseY });
        printf("<");
        gotoxy(letter->x, letter->y); // 수정: y 좌표로 변경
        printf("%c", letter->ch);

        // 마우스 클릭 상태 확인
        clickPoint(letter, &mousePos, &isDragging); // 수정: letter 포인터를 직접 전달

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

void gotoxy(int x, int y) {
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, Cur);
}

void clickPoint(LETTER* letter, POINT* mousePos, int* isDragging)
{
    int mouseX = mousePos->x / 9;  // 콘솔 문자 크기에 맞게 조정
    int mouseY = mousePos->y / 19; // 콘솔 문자 크기에 맞게 조정

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 || GetAsyncKeyState(VK_RBUTTON) & 0x8000)
    {
        // 마우스 클릭이 문자 'O'와 같은 좌표일 때
        if (mouseX == letter->x && mouseY == letter->y)
        {
            // 드래그 시작
            *isDragging = 1;
        }
        // 드래그 중일 때 알파벳 위치 업데이트
        if (*isDragging) // 수정: 포인터를 통해 값 확인
        {
            letter->x = mouseX;
            letter->y = mouseY;
        }
    }
    else
    {
        // 마우스 버튼이 떼어지면 드래그 종료
        *isDragging = 0;
    }
}
