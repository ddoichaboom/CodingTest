#include "pch.h"

// 문제 
// 머쓱이네 피자가게는 피자를 일곱 조각으로 잘라 줍니다. 
// 피자를 나눠먹을 사람의 수 n이 주어질 때, 
// 모든 사람이 피자를 한 조각 이상 먹기 위해 필요한 피자의 수를 return 하는 solution 함수를 완성해보세요.

// 조건 
// 1 ≤ n ≤ 100

#define PIZZA 7

int Solution(int n)
{
	int iAnswer(0);

	if ((n % PIZZA) == 0)
	{
		iAnswer = n / PIZZA;
	}
	else if ((n % PIZZA) != 0)
	{
		iAnswer = n / PIZZA + 1;
	}

	return iAnswer;
}

int main()
{
	int iInput(0);

	cout << "피자를 먹을 사람은 총 몇명입니까? : ";
	cin >> iInput;

	cout << "피자는 최소 " << Solution(iInput) << " 판이 필요합니다." << endl;

	return 0;
}