/*
此程序针对第一步的AA_COS结果来做推荐，要注意与降维前不同，此处的AA_COS结果是n*n的，
故而直接针对每一行进行top N选择。
PS：本程序所使用算法除select top N算法外均为最优时间复杂度 
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

fstream fout("aa&at_rs.txt", ios::out);//打开文件，供写

struct node
{
	long ua;
	long ub;
	double cos;
	node *next;
};

node* mp[28703];
node* topn[28703];

//读入算法现在已是线性时间复杂度，O(2n)
bool read_data()
{
	for(int i=1;i<=28702;i++)
	{
		mp[i]=new node();
		mp[i]->ua=0;//mp[i]号用户所对应的cos值的个数存储在ua中 
	} 
	
	fstream infile;
	infile.open("cos_clean.txt", ios::in);
	
	while(!infile.eof())
	{
		long ua,ub;
		double tcos;
		infile>>ua>>ub>>tcos;
		
		node *p=mp[ua];
		
		if(ua==ub)//important!!!
			continue;
		
		node *t=new node();
		t->ua=ua;
		t->ub=ub;
		t->cos=tcos;
		//头插 
		t->next=p->next;
		p->next=t;
		(p->ua)++;
		
		if(ub==1)
			cout<<"reading : "<<ua<<endl;
	}

	return true;
}

//子算法1:对数据量小于N的对象，只进行升序排序 
bool smallselect(int i,int N)
{
	node *p=mp[i];
	node *q=topn[i];
			
	p=p->next;
	node *t=new node();
	t->ua=p->ua;
	t->ub=p->ub;
	t->cos=p->cos;
	t->next=q->next;
	q->next=t;
	(topn[i]->ua)++;
	p=p->next;
			
	while(p)
	{
		t=new node();
		t->ua=p->ua;
		t->ub=p->ub;
		t->cos=p->cos;
				
		node *r=topn[i];//r用于找位置
		while(r->next!=NULL&&t->cos>r->next->cos)
			r=r->next;
				
		t->next=r->next;
		r->next=t;
				
		p=p->next;
		(topn[i]->ua)++;
	}
	
	return true;
}

//子算法2：对数据量大于N的对象，筛选cos值的top N行 
bool bigselect(int i,int N)
{
	node *p=mp[i];
	topn[i]->ua=N;
			
	p=p->next;
	node data[N];
	for(int j=0;j<N;j++)
	{
		data[j].ua=p->ua;
		data[j].ub=p->ub;
		data[j].cos=p->cos;
		p=p->next;
	}
			
	while(p)
	{
		double min=2;//cos最大为1 
		int index=-1;
		bool flag=false;
		for(int j=0;j<N;j++)
		{
			if(/*(min-data[j].cos)>eps*/data[j].cos<min)//data[j].cos<min
			{
				index=j;
				min=data[j].cos;
				flag=true;
			}
		}
		if(flag&&(p->cos)>min)
		{
			data[index].cos=p->cos;
			data[index].ua=p->ua;
			data[index].ub=p->ub;
		}
		
		p=p->next;
	}
			
	node *q=topn[i];
	for(int j=0;j<N;j++)
	{
		node *t=new node();
		t->ua=data[j].ua;
		t->ub=data[j].ub;
		t->cos=data[j].cos;
		
		t->next=q->next;
		q->next=t;
		q=q->next;
	}
	
	return true;
}

//top N选择算法,若不足N则全选
bool select_N(int N)
{
	for(int i=1;i<=28702;i++)
	{
		topn[i]=new node();
		topn[i]->ua=0;//ua记录本行实际选择的节点数目 
	}
	
	for(int i=1;i<=28702;i++)
	{
		node *p=mp[i];
		
		if((p->ua)<=0)
			goto A;//???
			
		if((p->ua)<=N)//深复制 
			smallselect(i,N);
		
		if((p->ua)>N)
			bigselect(i,N);
		
		A:
			cout<<"finished:"<<i<<endl;
	}
	
	return true;
}

//topn计算结果写入文本算法
bool writefile()
{
	for(int i=1;i<=28702;i++)
	{
		node *p=topn[i];
		if(p->ua<=0)
			continue;
		//fout<<"for user-"<<i<<",recommend information "<<p->ua<<":"<<endl;
		p=p->next;
		while(p)
		{
			fout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
			p=p->next;
		}
	}
	
	return true;
}

int main()
{
	if(read_data())
		cout<<"read data over!"<<endl;
	/* 
	//读数据算法正确性验证 
	node *p=mp[1]->next;
	while(p)
	{
		cout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
		p=p->next;
	}
	p=mp[70]->next;
	while(p)
	{
		cout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
		p=p->next;
	}
	*/ 
	/* 
	//每一行数据统计 
	for(int i=1;i<=28702;i++)
	{
		if(mp[i]->ua>0)
			fout<<i<<" "<<mp[i]->ua<<endl;
	} 
	*/
	
	select_N(3);
	
	
	//排序算法测试,recomand check point:small->534,637;big->524,457
	node *p=mp[25000]->next;
	while(p)
	{
		cout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
		p=p->next;
	}
	cout<<"*************************************"<<endl;
	p=topn[25000];
	while(p)
	{
		cout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
		p=p->next;
	}
	
	writefile();
	
	return 0;
}
