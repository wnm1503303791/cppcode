/*
此插件用于将刘泽奇的降维结果按照用户编号排序 
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
	long name;
	double data[4];
	node *next;
};

node *head;

bool sroting()
{
	fstream f1;
    f1.open("aa_at_pre4.txt", ios::in);
    
    head=new node();
    head->name=-1;
    
    while(!f1.eof())
    {
    	long tname;
    	double tdata[4];
    	f1>>tname>>tdata[0]>>tdata[1]>>tdata[2]>>tdata[3];
    	
    	node *t=new node();
    	t->name=tname;
    	t->data[0]=tdata[0];
    	t->data[1]=tdata[1];
    	t->data[2]=tdata[2];
    	t->data[3]=tdata[3];
    	
    	node *p=head;
    	node *q=head->next;
    	
    	while(p)
    	{
    		if(q==NULL)//扫到链表尾部 
	    		break;
			
			if(t->name>p->name&&q->name>t->name)//找到合适的位置 
				break;
			
			
			p=p->next;
			q=q->next;
		}
		
		t->next=q;
		p->next=t; 
	}
    
    return true;
}

bool test()
{
	node *p=head->next;
	node *q=p->next;
	while(q)
	{
		if(q->name-1!=p->name)
			cout<<"test error:"<<p->name<<","<<q->name<<endl;
		p=p->next;
		q=q->next;
	}
	
	return true;
}

bool writing_file()
{
	fstream fout("aa_at_pre4_sort.txt", ios::out);
	
	node *p=head->next;
	while(p)
	{
		fout<<p->name<<" "<<p->data[0]<<" "<<p->data[1]<<" "<<p->data[2]<<" "<<p->data[3]<<endl;
		p=p->next;
	}
}

int main()
{
	cout<<"sorting..."<<endl;
	sroting();
	
	cout<<"testing..."<<endl;
	test();
	
	cout<<"writing..."<<endl;
	writing_file();
	
	return 0;
}
