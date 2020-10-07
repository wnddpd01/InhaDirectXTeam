// HackerLank_practice.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;
#include <string>
//int main() {
//	int in;
//	string num[10] = { "greater than 9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
//
//	cin >> in;
//
//	if (in > 9) {
//		cout << num[0];
//	}
//	else {
//		cout << num[in];
//	}
//
//	return 0;
//}


int main()
{
	int n;
	cin >> n;

	string num[10] = { "Greater than 9", "one", "two", "three", "four","five","six","seven","eight","nine" };

	if( n > 9 )
		cout << num[0];
	else
		cout << num[n];
	
	return 0;
}
