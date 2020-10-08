// HackerRank5.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;
#include <string>


int main()
{
	int a, b, n;
	cin >> a >> b;


	string num[9] = { "one", "two", "three", "four","five", "six",  "seven","eight", "nine" };

	for (n = a; n <= b; n++)
	{
		if ((1 <= n) && (n <= 9))
		{
			cout << num[n - 1] << endl;
		}
		else if ((n > 9) && (n % 2 == 0))
			cout << "even" << endl;
		else
			cout << "odd" << endl;
	}


	return 0;
}

