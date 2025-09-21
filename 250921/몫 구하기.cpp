#include "pch.h"

// 제한 사항
// 0 < num1 <= 100
// 0 < num2 <= 100


int Solution(int num1, int num2)
{
	return num1 / num2;
}

int main()
{
	// Test

	cout << "5를 2로 나눈 몫 : " << Solution(5, 2) << endl;

	return 0;

}

