// Hacker Rank dynamic allocation.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;
	int *ptr;
	ptr = new int[1000];

	// cout<< endl<<"4개 만큼 배열을 동적할당해주고 입력도 4개 받아서 역순으로 출력 :"<<endl;
	// cout << "입력시작" << endl << endl <<"몇개의 정수를 입력할거야?  (0<=n<=1000)"<<endl;

	cin >> n;

	for ( int i = 0; i<n; i++ )
	{
		cin >> ptr[i];
	}

	// cout<<endl<<"역순으로 출력 시작"<<endl<<endl;

	for ( int i = n - 1; i >= 0; i-- )
	{
		cout << ptr[i] << " ";
	}
    return 0;
}

