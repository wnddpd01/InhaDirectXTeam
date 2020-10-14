
#include "stdafx.h"
#include  <iostream>
#include <string>
using namespace  std;

#define MAX_COUNT 5
#define MAX 10

int main()
{

	int n;
	int *ptr;
	ptr = new int[4];

	// cout<< endl<<"4개 만큼 배열을 동적할당해주고 입력도 4개 받아서 역순으로 출력 :"<<endl;
	// cout << "입력시작" << endl << endl <<"몇개의 정수를 입력할거야?  (0<=n<=1000)"<<endl;

	cin >> n;

	for ( int i = 0; i < 4; i++ )
	{
		cin >> ptr[i];
	}

	// cout<<endl<<"역순으로 출력 시작"<<endl<<endl;

	for ( int i = 3; i >= 0; i-- )
	{
		cout << ptr[i] << " ";
	}
	
	return 0;
}

	
	
	
	
	
