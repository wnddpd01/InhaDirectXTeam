// Hacker Rank 20 vector.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include  <string>
using namespace std;



// 선언하고 크기얼만지, 마지막 요소 꺼내고 정렬해보자

int main()
{
	

	//cout << "정수를 벡터뒤에 넣어보자 n(출력갯수) 입력 : ";

	//cin >> n;

	//for ( int i = 0; i < n; i++ )
	//{
	//	cin >> e;					// e 입력받고
	//	v.push_back( e );			// 벡터 제일 뒤에 입력받은걸 삽입
	//	/*cout << v[i] << endl;*/		// 0부터 1씩 증가하면서 순서대로 출력
	//}								// 이걸 반복 ,, 내가 입력숫자를 벡터에 넣고 출력
	//cout << endl << endl << endl;
	//for ( int j = 0; j < n; j++ )
	//{
	//	cout << v[j] << endl;
	//}

	//v.pop_back(); // 마지막 요소 꺼내고 다시 출력해보기 마지막 요소가 없는지

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
	1. 벡터생성
	2. 벡터안에 push_back으로 입력값 넣어주기
	3. 그냥 sort함수 이용해서 벡터 안의 값 정렬하기
	*/
	int n , e;
	vector<int>v;
	
	cout << "정수를 벡터뒤에 넣어보자 n(출력갯수) 입력 : ";
	
	cin >> n;
	cout << "넣을 값을 입력하세요 : ";
	
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
	//	cout << v[i] << " ";	// 벡터 넣은거 출력 형식 맞춰서(제일 앞 제일 뒤 그 다음 앞 그 다음 뒤 순서로 출력)
	//	cout << v[v.size() - (i+ 1)] << " ";
	//	
	//}
	
    return 0;
}

