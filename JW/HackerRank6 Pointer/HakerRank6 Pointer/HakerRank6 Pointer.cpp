// HakerRank6 Pointer.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
using namespace std;

void update(int *a, int *b)
{
	int result1 = *a + *b;
	int result2 = abs(*a - *b);

	cout << result1 << endl;
	cout << result2 << endl;
}


int main()
{
	int a, b;
	cin >> a >> b;
	update(&a, &b);
	
	return 0;
}



/*
#include <stdio.h>
#include <stdlib.h> 

void update(int *a, int *b) {
	// Complete this function
	int c = *a;
	*a = *a + *b;
	*b = (abs(c - *b));
}

int main() {
	int a, b;
	int *pa = &a, *pb = &b;

	scanf("%d %d", &a, &b);
	update(pa, pb);
	printf("%d\n%d", a, b);

	return 0;
}
*/