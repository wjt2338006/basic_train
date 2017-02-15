#include <iostream>
using namespace std;

#include "MyString.h"

int main()
{
	MyString s1("1234567");
	MyString s2=s1;
	s1 += s2;
	cout << s1;
}