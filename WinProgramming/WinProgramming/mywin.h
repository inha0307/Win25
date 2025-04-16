int getConsoleWidth();
int getConsoleHeight();
void move_cursor(int row, int col);


typedef struct Win 
{
    int x;              // ������ ���� ����Ʈ x
    int y;              // ������ ���� ����Ʈ y
    int width;          // �������� ũ�� (�ʺ�)
    int height;         // �������� ũ�� (����)
    char name[100];     // �������� �̸�
    int color;          // �������� �÷�
    int isMax;          // �������� �ִ�ȭ ���� (0: ���ִ�ȭ, 1: �ִ�ȭ)
}MyWin;

void DrawWin(MyWin a);