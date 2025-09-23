#include "pch.h"

// 문제
// 정수 배열 numbers가 매개변수로 주어집니다. 
// numbers의 원소 중 두 개를 곱해 만들 수 있는 
// 최댓값을 return하도록 solution 함수를 완성해주세요.

// 조건
// 0 ≤ numbers의 원소 ≤ 10,000
// 2 ≤ numbers의 길이 ≤ 100


// 아이디어
// 1. 최댓값 두 개를 찾은 뒤 해당 두 값의 곱을 최댓값으로 return 한다.
// 2. 해당 배열을 크기 순서대로 정렬 후 마지막 두 수의 곱을 return 한다.



int Solution(vector<int> numbers)
{
	int iNum(0);
	size_t iSize = numbers.size();

	for (size_t i = 0; i < iSize - 1; ++i)
	{
		for (size_t j = i + 1; j < iSize; ++j)
		{
			if (numbers[i] > numbers[j])
			{
				iNum = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = iNum;
			}
		}
	}

	return numbers[iSize - 1] * numbers[iSize - 2];


}

int main()
{
	vector<int>		vecNumbers;

	vecNumbers.push_back(0);
	vecNumbers.push_back(10);
	vecNumbers.push_back(31);
	vecNumbers.push_back(24);
	vecNumbers.push_back(8);
	vecNumbers.push_back(17);

	for (int i : vecNumbers)
	{
		cout << i << endl;
	}

	cout << Solution(vecNumbers);

	return 0;
}

