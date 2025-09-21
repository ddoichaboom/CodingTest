#include "pch.h"

#define CURRENT_YEAR 2025


int Solution(int age)
{
	int iBirthYear(0);

	iBirthYear = CURRENT_YEAR - age + 1;

	return iBirthYear;
}

int main()
{


	cout << "선생님의 나이는 27세, 출생년도는 " << Solution(27);

	return 0;

}