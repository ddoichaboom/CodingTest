#include "pch.h"

// 문제 
// 어떤 세균은 1시간에 두배만큼 증식한다고 합니다. 
// 처음 세균의 마리수 n과 경과한 시간 t가 매개변수로 주어질 때,
// t시간 후 세균의 수를 return하도록 solution 함수를 완성해주세요.

// 조건 
// 1 ≤ n ≤ 10
// 1 ≤ t ≤ 15

int Solution(int n, int t)
{
	int iAnswer = n;
	
	for (int i = 0; i < t; ++i)
	{
		iAnswer *= 2;
	}

	return iAnswer;
}

int main()
{
	int iInitGerm(0), iTime(0);
	cout << "초기 세균의 수 n, 경과한 시간 t 입력 : ";
	cin >> iInitGerm >> iTime;

	cout << "------------------------" << endl;
	cout << iTime << " 시간 후 세균의 수 : " << Solution(iInitGerm, iTime);

}