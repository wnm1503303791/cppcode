/*
�˲�����ڽ����û�������������ļ���Ϊ˳�� 
*/
#include<cstdio>  
#include<cstring>  
#include<algorithm>  
#include<iostream>  
#include<string>  
#include<vector>  
#include<stack>  
#include<bitset>  
#include<cstdlib>  
#include<cmath>  
#include<set>  
#include<list>  
#include<deque>  
#include<map>  
#include<queue>  
#include<fstream>
using namespace std; 

typedef long long ll;
const double PI = acos(-1.0);
const double eps = 1e-6;

struct node
{
	long a;
	long b;
	double cos;
	node *next;
};

int main()
{
	fstream f1;
    f1.open("aa5_sort.txt", ios::in);
    fstream fout("aa5_sort_reverse.txt", ios::out);
	
	node *head=new node();
	node *p=head;
	while(!f1.eof())
	{
		long user,term;
		double tcos;
		f1>>user>>term>>tcos;
		//ͷ�巨���������� 
		node *t=new node();
		t->a=user;
		t->b=term;
		t->cos=tcos;
		t->next=p->next;
		p->next=t;
	}
	
	cout<<"reading data over!"<<endl;
	
	p=head->next;
	while(p)
	{
		fout<<p->a<<" "<<p->b<<" "<<p->cos<<endl;
		p=p->next;
	}
	
	cout<<"writing data over!"<<endl;
	
	return 0;
}
