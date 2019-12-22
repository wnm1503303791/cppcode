/*************************************************************************
	> File Name: recursion.cpp
	> Author: tuzhuo
	> Mail: xmb028@163.com 
	> Created Time: Sun 03 Nov 2019 03:55:58 PM CST
 ************************************************************************/

#include<iostream>
#include<fstream>
using namespace std;

long MAX=10;

fstream outfile("killresult.txt", ios::out);//write file

int kill(int end)
{
	if(end>MAX)
		return false;
	else
	{
		kill(end+1);
		outfile<<"hello,world!"<<end<<endl;
		kill(end+1);
	}
	return true;
}

int main()
{
	kill(0);
}
