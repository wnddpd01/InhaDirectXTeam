// ī�乮�� 6. �ݺ��� (����ǥ ���).cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
using namespace std;




void MultiplicationTable()	// ���ϱ� ����� MultiplicationTable
{
	// 2~4��
	cout << "    2 \t\t    3\t\t   4" << endl;
	cout << "-------------------------------------------" << endl;
	for(int j=1;j<=9;j++) 
	{
		for ( int i = 2; i <= 4; i++ )
		{
			printf( "%d*%d = %2d\t" , i , j , i * j );	// %2d\t �� %d\t ���̴�  ���� ����
		}
		cout << endl;
	}
	cout << endl;

	cout << "    5 \t\t    6\t\t   7" << endl;
	cout << "-------------------------------------------" << endl;
	//5~7��
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
	//8~9��
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

