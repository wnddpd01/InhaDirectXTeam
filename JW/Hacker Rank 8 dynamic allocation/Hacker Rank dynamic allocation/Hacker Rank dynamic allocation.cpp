// Hacker Rank dynamic allocation.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

	// cout<< endl<<"4�� ��ŭ �迭�� �����Ҵ����ְ� �Էµ� 4�� �޾Ƽ� �������� ��� :"<<endl;
	// cout << "�Է½���" << endl << endl <<"��� ������ �Է��Ұž�?  (0<=n<=1000)"<<endl;

	cin >> n;

	for ( int i = 0; i<n; i++ )
	{
		cin >> ptr[i];
	}

	// cout<<endl<<"�������� ��� ����"<<endl<<endl;

	for ( int i = n - 1; i >= 0; i-- )
	{
		cout << ptr[i] << " ";
	}
    return 0;
}

