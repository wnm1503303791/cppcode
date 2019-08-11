/*
此程序根据第二步的面向aa的rs进行评估，主要根据author_label.txt判断所推荐的5个结果用户中是否有与用户相同label的用户。
只要5个中有一个命中，则认定该用户被推荐系统命中。
特别要指明：本程序不同于第一次使用的evaluation评价方法，此代码针对F-Score=(2*P*R)/(P+R)进行评估
top N中的N为推荐的个数，P表示N个中命中数除以N；R表示N个中命中数除以所有相同label
F-Score的取值为0～1之间的小数 
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

fstream fout("aa&at5_rs1_evaluation.md", ios::out);//打开文件，供写

struct node
{
	long ua;
	long ub;
	double cos;
	node *next;
};

int dict[28703];
node* mp[28703];
int labelnum[5];

ll read_data()
{
	fstream infile;
	infile.open("aa&at_rs.txt", ios::in);
	
	for(int i=1;i<=28702;i++)
		mp[i]=new node();
	/*
	mp[name]=new node();
	node *p=(mp[name]);
	*/
	node *p;
	long current_name=0;
	ll counter=0;
	
	while(!infile.eof())
	{
		counter++;
		long ua,ub;
		double tcos;
		infile>>ua>>ub>>tcos;
		if(ua>current_name)
		{
			current_name=ua;
			p=(mp[current_name]);
			cout<<"reading:"<<current_name<<endl;
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

	return counter;
}

bool read_label()
{
	fstream infile;
	infile.open("author_label.txt", ios::in);
	
	for(int i=1;i<=28702;i++)
		dict[i]=0;
	for(int i=1;i<=4;i++)//error!
		labelnum[i]=0;
	
	while(!infile.eof())
	{
		long user,label; 
		infile>>user>>label;
		
		dict[user]=label;
		(labelnum[label])++;
	}
	
	return true;
}

/* 
ll evaluating()
{
	ll target=0;
	
	for(int i=1;i<=28702;i++)
	{
		node *p=mp[i]->next;
		while(p)
		{
			if(dict[(p->ub)]==dict[i])
				target++;
			p=p->next;
		}
	}
	
	return target;
}
*/

/*
ll evaluating()
{
	ll target=0;
	
	for(int i=1;i<=28702;i++)
	{
		node *p=mp[i]->next;
		bool flag=false;
		while(p)
		{
			if(dict[(p->ub)]==dict[i])
				flag=true;
			p=p->next;
		}
		
		if(flag)
			target++;
	}
	
	return target;
} 
*/

bool evaluating()
{
	for(int i=1;i<=28702;i++)
	{
		/*
		if(dict[i]<=0)
			continue;
		*/
		
		//循环体内仅针对一个用户进行F-Score计算 
		ll target=0;
		node *p=mp[i]->next;
		while(p)
		{
			if(dict[(p->ub)]==dict[i])
				target++;
			p=p->next;
		}
		if(dict[i]>0)
		{
			double pc=(double)target/(mp[i]->ua);
			double r=(double)target/labelnum[dict[i]];
			double f=(2*pc*r)/(pc+r);
			
			if(pc>eps&&r>eps)
				fout<<i<<" "<<pc<<" "<<r<<" "<<f<<endl;
		}
	}
	
	return true;
}

int main()
{
	
	ll s_num=read_data();
	if(s_num)
		cout<<"read data over!"<<endl;
		
	if(read_label())
		cout<<"read label over!"<<endl;
	cout<<labelnum[1]<<" "<<labelnum[2]<<" "<<labelnum[3]<<" "<<labelnum[4]<<endl;
		
	if(evaluating())
		cout<<"evaluation over!"<<endl;
		
	
	/*
	fout<<"all recommend:"<<s_num<<endl;
	fout<<"target:"<<target<<endl;
	fout<<"P:"<<p<<endl;
	fout<<"R:"<<r<<endl;
	fout<<"F-Score:"<<(2*p*r)/(p+r)<<endl;
	*/
	
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
