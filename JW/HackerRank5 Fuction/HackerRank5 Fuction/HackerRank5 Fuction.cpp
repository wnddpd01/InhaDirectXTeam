// HackerRank5 Fuction.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string.h>
#include <string>
#include <iostream>
using namespace  std;



int sum_of_four()
{
	int max;
	int max_arr[4] ;

	
	cin >> max_arr[0] >> max_arr[1] >> max_arr[2] >> max_arr[3];
	
	max = max_arr[0];
	
	
	for(int i =1; i<4; i++)
	{
		if(max < max_arr[i])
		{
			max = max_arr[i];
		}
				
	}
	
	return max;
}


int main()
{
	cout << sum_of_four();
	
    return 0;
}

