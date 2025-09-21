#include "pch.h"

// Q. 정수 n이 주어질 때, n이하의 짝수를 모두 더한 값을 return 하도록 solution 함수를 작성해주세요.


int Solution(int n)
{
	int iSum(0);

	for (int i = 1; i < n+1; ++i)
	{
		if ((i % 2) == 0)
			iSum += i;
	}

	return iSum;
}

int main()
{
	cout << Solution(10);


	return 0;
}