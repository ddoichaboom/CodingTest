#include "pch.h"

// Q. 정수 배열 numbers가 매개변수로 주어집니다. 
// numbers의 원소의 평균값을 return하도록 solution 함수를 완성해주세요.

// 조건
// 0 ≤ numbers의 원소 ≤ 1,000
// 1 ≤ numbers의 길이 ≤ 100 
// 정답의 소수 부분이 .0 또는 .5인 경우만 입력으로 주어집니다.

double Solution(vector<int> numbers) {

	double answer(0);
	int iSum(0);
	size_t iSize = numbers.size();

	for (vector<int>::iterator		iter = numbers.begin();
		iter != numbers.end();
		++iter)
	{
		iSum += (*iter);
	}

	answer = static_cast<double>(iSum) / iSize;

	return answer;

}

int main()
{
	int iSum(0);
	vector<int>			vecNumber;

	for (int i = 0; i < 10; ++i)
	{
		vecNumber.push_back(i + 89);
		cout << vecNumber[i] << endl;
		iSum += vecNumber[i];
	}

	cout << "-----------------------------------------" << endl;
	cout << "배열의 총합 : " << iSum << " 배열의 크기 : " << vecNumber.size() << " 배열의 평균값 : " << Solution(vecNumber);


	return 0;
}