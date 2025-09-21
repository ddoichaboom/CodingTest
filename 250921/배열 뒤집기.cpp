#include "pch.h"

// 문제 - 배열 뒤집기
// 정수가 들어 있는 배열 num_list가 매개변수로 주어집니다.
// num_list의 원소의 순서를 거꾸로 뒤집은 배열을 return하도록 solution 함수를 완성해주세요.

// 조건
// 1 ≤ num_list의 길이 ≤ 1,000
// 0 ≤ num_list의 원소 ≤ 1,000


vector<int>	 Solution(vector<int> num_list)
{
	int iNum(0);
	size_t iSize = num_list.size();

	if ((num_list.size() % 2) == 0)
	{
		for (size_t i = 0; i < iSize / 2; ++i)
		{
			iNum = num_list[i];
			num_list[i] = num_list[iSize -1 - i];
			num_list[iSize - 1 - i] = iNum;
		}

		return num_list;
	}
	else
	{	
		for (size_t i = 0; i < (iSize / 2) + 1; ++i)
		{
			iNum = num_list[i];
			num_list[i] = num_list[iSize - 1 - i];
			num_list[iSize - 1 - i] = iNum;
		}
		return num_list;

	}
}

int main()
{
	vector<int>		vecNumList;
	vector<int>		vecSwapNumList;

	for (int i = 0; i < 10; ++i)
	{
		vecNumList.push_back(i + 1);
	}

	for (int i : vecNumList)
	{
		cout << i << endl;
	}

	vecSwapNumList = Solution(vecNumList);

	cout << "------------------------------" << endl;

	for (int i : vecSwapNumList)
	{
		cout << i << endl;
	}
	

	return 0;
}