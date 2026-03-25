#include<iostream>
using namespace std;


void test3()
{
	cout << "test3():"<< (void*)&test3 << endl;
}

void test2()
{
	cout << "test2():"<< (void*)&test2 << endl;
	test3();
}

void test1()
{
	int a=1;
	char b='2';
	int c=3;

	cout << "---stack variables define---" << endl;
	cout << "a:" << &a <<":"<<a<<endl;
	cout << "b:" << (void*)&b <<":"<<b<< endl;
	cout << "c:" << &c << ":"<<c<<endl;
}

int main()
{
	test1();

	return 0;
}