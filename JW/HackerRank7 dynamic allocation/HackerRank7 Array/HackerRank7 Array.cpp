
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

	// cout<< endl<<"4�� ��ŭ �迭�� �����Ҵ����ְ� �Էµ� 4�� �޾Ƽ� �������� ��� :"<<endl;
	// cout << "�Է½���" << endl << endl <<"��� ������ �Է��Ұž�?  (0<=n<=1000)"<<endl;

	cin >> n;

	for ( int i = 0; i < 4; i++ )
	{
		cin >> ptr[i];
	}

	// cout<<endl<<"�������� ��� ����"<<endl<<endl;

	for ( int i = 3; i >= 0; i-- )
	{
		cout << ptr[i] << " ";
	}
	
	return 0;
}

	
	
	
	
	
