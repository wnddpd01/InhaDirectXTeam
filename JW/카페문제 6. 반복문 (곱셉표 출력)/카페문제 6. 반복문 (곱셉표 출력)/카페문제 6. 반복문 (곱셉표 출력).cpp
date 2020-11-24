// 카페문제 6. 반복문 (곱셉표 출력).cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
using namespace std;




void MultiplicationTable()	// 곱하기 영어로 MultiplicationTable
{
	// 2~4단
	cout << "    2 \t\t    3\t\t   4" << endl;
	cout << "-------------------------------------------" << endl;
	for(int j=1;j<=9;j++) 
	{
		for ( int i = 2; i <= 4; i++ )
		{
			printf( "%d*%d = %2d\t" , i , j , i * j );	// %2d\t 와 %d\t 차이는  띄어쓰기 차이
		}
		cout << endl;
	}
	cout << endl;

	cout << "    5 \t\t    6\t\t   7" << endl;
	cout << "-------------------------------------------" << endl;
	//5~7단
	for ( int j = 1; j <= 9; j++ )
	{
		for ( int i = 5; i <= 7; i++ )
		{
			printf( "%d*%d = %2d\t" , i , j , i * j );	
		}
		cout << endl;
	}
	cout << endl;

	cout << "    8 \t\t    9\t\t " << endl;
	cout << "-------------------------------------------" << endl;
	//8~9단
	for ( int j = 1; j <= 9; j++ )
	{
		for ( int i = 8; i <= 9; i++ )
		{
			printf( "%d*%d = %2d\t" , i , j , i * j );
		}
		cout << endl;
	}
}

int main()
{
	MultiplicationTable();
	
    return 0;
}

