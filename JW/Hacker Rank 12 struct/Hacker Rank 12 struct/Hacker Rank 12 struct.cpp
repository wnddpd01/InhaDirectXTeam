// Hacker Rank 12 struct.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

struct Student
{
	int age;
	string first_name;
	string last_name;
	int standard;
};

int main()
{
	Student st;

	cin >> st.age >> st.first_name >> st.last_name >> st.standard;
	cout << st.age <<" "<< st.first_name << " " << st.last_name << " " << st.standard << " " << endl;
	
	
	
    return 0;
}

