// inha_cafe_number.18 dynamic allocation.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void dynamic_allocation()
{
	cout << endl << "���ڸ� �Է¹޾Ƽ� �Է� ���� ������ �޸𸮸� �÷����鼭 ó���ϴ� �ڵ带 �̿��� ���α�����§��." << endl << endl;

	cout << "�Է¹޴� ���ڴ� �ڿ����̰�, -1�� �ԷµǸ� �Է¹��� ���ڵ�� �� ���� ����ϰ� ���α׷��� ����" << endl << endl << endl;

	int n , sum = 0;
	int i,r,k;
	cout << "��� ���ڸ� �Է��Ұž�?" << endl;		// ex 5��
	cin >> n;
	cout << endl << endl << endl;

	
	int * ptr;
	ptr = new int[n];

	for ( i = 0; i < n; i++ )
	{
		cin >> ptr[i];
		
		if ( ptr[i] == -1 )					// �Է°��� -1�̸�
		{
			for ( r = 0; r < n; r++ )	// �迭 ptr[0] ���� ~ ptr[i-1]���� (�� i ��) ���Ѵ�. ���⼭ ptr[i]���� ptr[k]���� �𸣰���. 
			{
				sum += ptr[r];
			}

			cout << "-1�� �Է� �Ǿ����Ƿ� �� ���� : " << sum;	// �ε��� ������� ����� �ϰڴµ� ���ʷ� ���ϴ°� ���ϰ���	
													// break;  ��ġ ����
		}
	}

	
	//for(int k=0; k<n; k++)
	//{
	//	if ( ptr[i] == -1 )					// �Է°��� -1�̸�
	//	{
	//		for ( r = 0; r < ptr[i]; r++ )	// �迭 ptr[0] ���� ~ ptr[i-1]���� (�� i ��) ���Ѵ�. ���⼭ ptr[i]���� ptr[k]���� �𸣰���. 
	//		{
	//			sum += ptr[r];
	//		}

	//		cout << "-1�� �Է� �Ǿ����Ƿ� �� ���� : " << sum;	// �ε��� ������� ����� �ϰڴµ� ���ʷ� ���ϴ°� ���ϰ���	
	//												// break;  ��ġ ����
	//	}
	//}
	//
	
		
	delete[] ptr;

}


int main()
{
	dynamic_allocation();

	return 0;
}

