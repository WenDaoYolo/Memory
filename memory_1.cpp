#include<iostream>
#include<assert.h>
using namespace std;

struct test1{      
	char a;       //偏移0
	float b;      //偏移4~7
	char c;       //偏移8
};                //最终对齐大小：12个字节

struct test2{     
	char a;       //偏移0
	char c;       //偏移1
	float b;      //偏移4~7
};                //最终对齐大小：8个字

int main()
{
	cout<<sizeof(test1)<<" "<<sizeof(test2)<<endl;

	return 0;
}