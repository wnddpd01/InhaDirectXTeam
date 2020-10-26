// HackerRank 8 Variable Sized Arrays.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include  <string>
using namespace std;
class Student
{
private:

	int age , standard;
	string first_name , last_name;

public:
	void set_age(); int get_age();
	void set_standard();
	void set_first_name();
	void set_last_name();

};


int main()
{
	/*string a = "abcd";
	string b = "ef";
	string c = a + b;*/

	string a;
	string b;
	string c = a + b;
	string temp = "abc";
	
	cin >> a >> b;

	

	cout << a.size() << " " << b.size() << endl;
	cout << a + b << endl;

	temp[0] = a[0];
	a[0] = b[0];
	b[0] = temp[0];

	cout << a << " " << b << endl;

		
}




//
//int main()
//{
//	int age , standard;
//	string first_name , last_name;
//
//	cin >> age >> first_name >> last_name >> standard;
//
//	Student st;
//	st.set_age( age );
//	st.set_standard( standard );
//	st.set_first_name( first_name );
//	st.set_last_name( last_name );
//
//	cout << st.get_age() << "\n";
//	cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
//	cout << st.get_standard() << "\n";
//	cout << "\n";
//	cout << st.to_string();
//	
//	
//	
//    return 0;
//}

