// Hacker Rank 12 struct.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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

