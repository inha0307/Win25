#include <stdio.h>
#include <Windows.h>

int PassOrFail(int score);

int main()
{
	int score = 70;
	if (PassOrFail(70))
	{
		printf("재시험 없습니다!");
	}
	else
		printf("우리는 망했다…  재시험이다…");

}



PassOrFail(int score)
{
	if (score >= 50)
		return 1;
	else
		return 0;
}