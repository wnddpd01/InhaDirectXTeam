#pragma once

// HackerRank Class.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
using namespace  std;
#include <iostream>
#include  <string>
#include <vector>

class Student
{
private:
	int m_age , m_standard;
	string m_first_name , m_last_name;

public:
	Student();
	~Student();

	int get_age()
	{
		return m_age;
	}
	string get_first_name() { return m_first_name; }
	string get_last_name() { return m_last_name; }
	int get_standard() { return m_standard; }

	
	int set_age( int external_age )
	{
		return m_age = external_age;
	}
	
	string set_first_name( string external_first_name )
	{
		return m_first_name = external_first_name;
	}
	
	string set_last_name( string external_last_name )
	{
		return m_last_name = external_last_name;
	}
	
	int set_standard( int external_standard )
	{
		return m_standard = external_standard;
	}

	
};
