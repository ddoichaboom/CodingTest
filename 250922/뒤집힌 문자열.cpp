#include "pch.h"

// 문제
// 문자열 my_string이 매개변수로 주어집니다. 
// my_string을 거꾸로 뒤집은 문자열을 return하도록 solution 함수를 완성해주세요.

// 조건
// 1 ≤ my_string의 길이 ≤ 1,000


string Solution(string my_string)
{
	char	cTmp(0);
	int iLength = my_string.length();
	

	for (int i = 0; i < iLength / 2; ++i)
	{
		cTmp = my_string[i];
		my_string[i] = my_string[iLength - i -1];
		my_string[iLength - i - 1] = cTmp;
	}

	return my_string;
}

int main()
{
	string sMyString = "Hello World";

	cout << Solution(sMyString);

	return 0;
}


