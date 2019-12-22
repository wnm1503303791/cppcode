/*************************************************************************
	> File Name: hello.cpp
	> Author: tuzhuo
	> Mail: xmb028@163.com 
	> Created Time: Sun 03 Nov 2019 03:46:52 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int helloworld()
{
	cout<<"hello,tuzhuo!"<<endl;

	return 1;
}

int main()
{
	while(1)
	{
		if(helloworld())
			break;
	}

	return 0;
}
