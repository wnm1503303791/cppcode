/*
�˳�����Ե�һ����AA_COS��������Ƽ���Ҫע���뽵άǰ��ͬ���˴���AA_COS�����n*n�ģ�
�ʶ�ֱ�����ÿһ�н���top Nѡ��
PS����������ʹ���㷨��select top N�㷨���Ϊ����ʱ�临�Ӷ� 
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

fstream fout("aa&at_rs.txt", ios::out);//���ļ�����д

struct node
{
	long ua;
	long ub;
	double cos;
	node *next;
};

node* mp[28703];
node* topn[28703];

//�����㷨������������ʱ�临�Ӷȣ�O(2n)
bool read_data()
{
	for(int i=1;i<=28702;i++)
	{
		mp[i]=new node();
		mp[i]->ua=0;//mp[i]���û�����Ӧ��cosֵ�ĸ����洢��ua�� 
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
		//ͷ�� 
		t->next=p->next;
		p->next=t;
		(p->ua)++;
		
		if(ub==1)
			cout<<"reading : "<<ua<<endl;
	}

	return true;
}

//���㷨1:��������С��N�Ķ���ֻ������������ 
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
				
		node *r=topn[i];//r������λ��
		while(r->next!=NULL&&t->cos>r->next->cos)
			r=r->next;
				
		t->next=r->next;
		r->next=t;
				
		p=p->next;
		(topn[i]->ua)++;
	}
	
	return true;
}

//���㷨2��������������N�Ķ���ɸѡcosֵ��top N�� 
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
		double min=2;//cos���Ϊ1 
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

//top Nѡ���㷨,������N��ȫѡ
bool select_N(int N)
{
	for(int i=1;i<=28702;i++)
	{
		topn[i]=new node();
		topn[i]->ua=0;//ua��¼����ʵ��ѡ��Ľڵ���Ŀ 
	}
	
	for(int i=1;i<=28702;i++)
	{
		node *p=mp[i];
		
		if((p->ua)<=0)
			goto A;//???
			
		if((p->ua)<=N)//��� 
			smallselect(i,N);
		
		if((p->ua)>N)
			bigselect(i,N);
		
		A:
			cout<<"finished:"<<i<<endl;
	}
	
	return true;
}

//topn������д���ı��㷨
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
	//�������㷨��ȷ����֤ 
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
	//ÿһ������ͳ�� 
	for(int i=1;i<=28702;i++)
	{
		if(mp[i]->ua>0)
			fout<<i<<" "<<mp[i]->ua<<endl;
	} 
	*/
	
	select_N(3);
	
	
	//�����㷨����,recomand check point:small->534,637;big->524,457
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
