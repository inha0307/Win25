#include <stdio.h>
#include <Windows.h>

int PassOrFail(int score);

int main()
{
	int score = 70;
	if (PassOrFail(70))
	{
		printf("����� �����ϴ�!");
	}
	else
		printf("�츮�� ���ߴ١�  ������̴١�");

}



PassOrFail(int score)
{
	if (score >= 50)
		return 1;
	else
		return 0;
}