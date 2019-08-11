/*
本代码专门用于实打实的计算混合相似度，aa与at混合比值为1:2 
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

fstream fout("hybrid_cos_2.txt", ios::out);//打开文件，供写

struct node
{
	long ua;
	long ub;
	double fitness;
	node *next;
};

node* mpaa[28703];

bool read_data_at(double at[],long current_name)
{
	fstream in2;
	in2.open("at_cos.txt", ios::in);
	/*
	mp[name]=new node();
	node *p=(mp[name]);
	*/

	while(!in2.eof())
	{
		long ua,ub;
		double fitness;
		in2>>ua>>ub>>fitness;
		if(ua>current_name)
			break ;
		if(ua==current_name)
			at[ub]=fitness;
	}

	return true;
}

bool read_data_aa()
{
	fstream in1;
	in1.open("aa_cos.txt", ios::in);
	/*
	mp[name]=new node();
	node *p=(mp[name]);
	*/
	node *p;
	long current_name=0;
	
	while(!in1.eof())
	{
		long ua,ub;
		double fitness;
		in1>>ua>>ub>>fitness;
		if(ua>current_name)
		{
			current_name=ua;
			p=(mpaa[current_name]);
		}
		if(ua==current_name)
		{
			node *t=new node();
			t->ua=ua;
			t->ub=ub;
			t->fitness=fitness;
				
			p->next=t;
			p=p->next;
		}
	}

	return true;
}

bool calculate(double aa[],double at[],double t[])
{
	for(int i=1;i<=28702;i++)
	{
		t[i]=aa[i]+2*at[i];
		//cout<<i<<":"<<aa[i]<<" "<<at[i]<<" "<<t[i]<<endl;
	}
	
	return true;
}



int main()
{
	for(int i=1;i<=28702;i++)
		mpaa[i]=new node();
	read_data_aa();
	
	for(int i=11727;i<=28702;i++)
	{
		cout<<i<<endl;
		
		double aa[28703],at[28703],h[28703];
		for(int j=1;j<=28702;j++)
		{
			aa[j]=0;
			at[j]=0;
			h[j]=0;
		}
		
		node *p=mpaa[i]->next;
		while(p)
		{
			aa[p->ub]=p->fitness;
			p=p->next;
		}
		read_data_at(at,i);
		
		calculate(aa,at,h);
		
		for(int j=1;j<=28702;j++)
		{
			if(h[j]>eps)
				fout<<i<<" "<<j<<" "<<h[j]<<endl;
		}
	}
	
	return 0;
}
