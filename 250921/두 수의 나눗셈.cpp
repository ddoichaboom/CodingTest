#include "pch.h"

// Q. num1 을 num2로 나눈 값에 1,000을 곱한 후 정수 값을 return하는 Solution 함수

int Solution(int num1, int num2)
{
	float fResult = static_cast<float>(num1) / static_cast<float>(num2);
	int iResult = fResult * 1000;

	return iResult;
	
	
}

int main()
{
	cout << Solution(1, 16) << endl;

	return 0;

}