// HackerLank_practice.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
