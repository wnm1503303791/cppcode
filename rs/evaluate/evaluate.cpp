/*
此程序根据第二步的面向aa和at的rs进行评估，主要根据author_label.txt判断所推荐的5个结果用户中是否有与用户相同label的用户。
只要5个中有一个命中，则认定该用户被推荐系统命中。
特别要指明：没有在author_label.txt文件中被标label的用户，其在文件at_rs.txt中的推荐结果不纳入本次评估 
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

fstream fout("hybrid_rs_evaluation.txt", ios::out);//打开文件，供写

struct node
{
	long ua;
	long ub;
	double cos;
	node *next;
};

int dict[28703];
node* mp[28703];

bool read_data()
{
	fstream infile;
	infile.open("hybrid_rs.txt", ios::in);
	
	for(int i=1;i<=28702;i++)
		mp[i]=new node();
	/*
	mp[name]=new node();
	node *p=(mp[name]);
	*/
	node *p;
	long current_name=0;
	
	while(!infile.eof())
	{
		long ua,ub;
		double tcos;
		infile>>ua>>ub>>tcos;
		if(ua>current_name)
		{
			current_name=ua;
			p=(mp[current_name]);
		}
		if(ua==current_name)
		{
			node *t=new node();
			t->ua=ua;
			t->ub=ub;
			t->cos=tcos;
				
			p->next=t;
			p=p->next;
			
			(mp[current_name]->ua)++;
		}
	}

	return true;
}

bool read_label()
{
	fstream infile;
	infile.open("author_label.txt", ios::in);
	
	for(int i=1;i<=28702;i++)
		dict[i]=0;
	
	while(!infile.eof())
	{
		long user,label; 
		infile>>user>>label;
		
		dict[user]=label;
	}
	
	return true;
}

ll evaluating()
{
	ll target=0;
	
	for(int i=1;i<=28702;i++)
	{
		node *p=mp[i]->next;
		bool flag=false;
		while(p)
		{
			if(dict[(p->ub)]==dict[i]&&dict[i]!=0)
				flag=true;
			p=p->next;
		}
		
		if(flag)
			target++;
	}
	
	return target;
}


int main()
{
	if(read_data())
		cout<<"read data over!"<<endl;
		
	if(read_label())
		cout<<"read label over!"<<endl;
		
	ll target=evaluating();
	double sum=4236;
	double rate=target/sum;
	
	fout<<"all:28702"<<endl;
	fout<<"target:"<<target<<endl;
	fout<<"targeting rate:"<<rate<<endl;
	
	/*
	node *p=mp[6172];
	while(p)
	{
		cout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
		p=p->next;
	}
	*/
	
	return 0;
}
