// inha_cafe_number.18 dynamic allocation.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void dynamic_allocation()
{
	cout << endl << "숫자를 입력받아서 입력 받을 때마다 메모리를 늘려가면서 처리하는 코드를 이용해 프로구램을짠다." << endl << endl;

	cout << "입력받는 숫자는 자연수이고, -1이 입력되면 입력받은 숫자들과 그 합을 출력하고 프로그램을 종료" << endl << endl << endl;

	int n , sum = 0;
	int i,r,k;
	cout << "몇개의 숫자를 입력할거야?" << endl;		// ex 5개
	cin >> n;
	cout << endl << endl << endl;

	
	int * ptr;
	ptr = new int[n];

	for ( i = 0; i < n; i++ )
	{
		cin >> ptr[i];
		
		if ( ptr[i] == -1 )					// 입력값이 -1이면
		{
			for ( r = 0; r < n; r++ )	// 배열 ptr[0] 부터 ~ ptr[i-1]까지 (총 i 개) 더한다. 여기서 ptr[i]인지 ptr[k]인지 모르겠음. 
			{
				sum += ptr[r];
			}

			cout << "-1이 입력 되었으므로 총 합은 : " << sum;	// 인덱스 순서대로 출력은 하겠는데 차례로 더하는걸 못하겠음	
													// break;  위치 변경
		}
	}

	
	//for(int k=0; k<n; k++)
	//{
	//	if ( ptr[i] == -1 )					// 입력값이 -1이면
	//	{
	//		for ( r = 0; r < ptr[i]; r++ )	// 배열 ptr[0] 부터 ~ ptr[i-1]까지 (총 i 개) 더한다. 여기서 ptr[i]인지 ptr[k]인지 모르겠음. 
	//		{
	//			sum += ptr[r];
	//		}

	//		cout << "-1이 입력 되었으므로 총 합은 : " << sum;	// 인덱스 순서대로 출력은 하겠는데 차례로 더하는걸 못하겠음	
	//												// break;  위치 변경
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

