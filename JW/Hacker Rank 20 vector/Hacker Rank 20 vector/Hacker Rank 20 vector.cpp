// Hacker Rank 20 vector.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include  <string>
using namespace std;



// �����ϰ� ũ�����, ������ ��� ������ �����غ���

int main()
{
	

	//cout << "������ ���͵ڿ� �־�� n(��°���) �Է� : ";

	//cin >> n;

	//for ( int i = 0; i < n; i++ )
	//{
	//	cin >> e;					// e �Է¹ް�
	//	v.push_back( e );			// ���� ���� �ڿ� �Է¹����� ����
	//	/*cout << v[i] << endl;*/		// 0���� 1�� �����ϸ鼭 ������� ���
	//}								// �̰� �ݺ� ,, ���� �Է¼��ڸ� ���Ϳ� �ְ� ���
	//cout << endl << endl << endl;
	//for ( int j = 0; j < n; j++ )
	//{
	//	cout << v[j] << endl;
	//}

	//v.pop_back(); // ������ ��� ������ �ٽ� ����غ��� ������ ��Ұ� ������

	//cout << endl << endl << endl;
	//for ( int j = 0; j < v.size(); j++ )
	//{
	//	cout << v[j] << endl;
	//}

	//sort( v.begin() , v.end() );

	//cout << endl << endl << endl;
	//for ( int j = 0; j < v.size(); j++ )
	//{
	//	cout << v[j] << endl;
	//}

	// ======================================
	/*
	1. ���ͻ���
	2. ���;ȿ� push_back���� �Է°� �־��ֱ�
	3. �׳� sort�Լ� �̿��ؼ� ���� ���� �� �����ϱ�
	*/
	int n , e;
	vector<int>v;
	
	cout << "������ ���͵ڿ� �־�� n(��°���) �Է� : ";
	
	cin >> n;
	cout << "���� ���� �Է��ϼ��� : ";
	
	for ( int i = 0; i < n; i++ )
	{
		cin >> e;
		v.push_back( e );		
	}

	sort( v.begin() , v.end() );

	for(int i=0; i<v.size(); i++)
	{
		cout << v[i] << " ";
	}
	
	/*for ( int i = 0; i < n; i++ )
	{
		cout << v[i] << " ";
		cout << v[n - 1] << " ";
		cout << v[i + 1] << " ";
		cout << v[n - 2] << " ";
		cout << v[i + 2] << " ";
	}*/
	

	
	//for ( int i = 0; i < v.size()/2; i++ )
	//{
	//	cout << v[i] << " ";	// ���� ������ ��� ���� ���缭(���� �� ���� �� �� ���� �� �� ���� �� ������ ���)
	//	cout << v[v.size() - (i+ 1)] << " ";
	//	
	//}
	
    return 0;
}

