// HackerRank Class.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
using namespace  std;
#include <iostream>
#include  <string>
#include <vector>
#include "Student.h"

int main()
{
	Student st;

	int external_age , external_standard;
	string external_first_name , external_last_name;

	cout << "input start ! " << endl << " Enter in it this order: age, m_first_name, m_last_name, standard" << endl << endl;

	cin >> external_age >> external_first_name >> external_last_name >> external_standard;
	
	cout << st.get_age() << endl << endl;		// �����ڿ��� �ʱⰪ�� 0���� ���� 0�� ����
	
	st.set_age( external_age );
	cout << st.get_age() << endl;

	st.set_first_name( external_first_name );
	

	st.set_last_name( external_last_name );
	cout << st.get_first_name() << ", " << st.get_last_name() << endl;

	st.set_standard( external_standard );
	cout << st.get_standard() << endl << endl;
	
	cout << st.get_age() <<","<< st.get_first_name() << "," << st.get_last_name() << "," << st.get_standard() << endl;
	


	return 0;
}


/*
	cin >> external_age >> external_first_name >> external_last_name >> external_standard;

	cout << "input start ! " << endl << " Enter in it this order: age, m_first_name, m_last_name, standard" << endl << endl;

	cout << st.get_age( external_age ) << endl;
	cout << st.get_last_name( external_last_name ) << st.set_first_name( external_first_name ) << endl;
	st.set_standard( external_standard );

	cout << st.
 */