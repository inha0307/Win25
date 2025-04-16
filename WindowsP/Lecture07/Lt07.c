#include <stdio.h>
#include <Windows.h>
#include <conio.h>


int main()
{
	while (1)
	{
		printf("\x1B[0;0H ~(-_- )~");
		Sleep(400);
		system("cls");
		printf("\x1B[2;0H ~( -_-)~");
		Sleep(400);
		system("cls");
	}
	return 0;
}