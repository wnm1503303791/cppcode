/*
�˳�����Ե�һ����AA_COS��������Ƽ���Ҫע��AA_COS����������ǵģ��ʶ�Ҫ���������ǵ����ݣ������ÿһ�н���top Nѡ��
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

fstream fout("hybrid_rs.txt", ios::out);//���ļ�����д

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
	infile.open("hybrid_cos_sum.txt", ios::in);
	
	ll count=0;
	
	while(!infile.eof())
	{
		long ua,ub;
		double tcos;
		infile>>ua>>ub>>tcos;
		
		node *p1=mp[ua];
		node *p2=mp[ub];
		
		node *t1=new node();
		t1->ua=ua;
		t1->ub=ub;
		t1->cos=tcos;
		//ͷ�� 
		t1->next=p1->next;
		p1->next=t1;
		(p1->ua)++;
		
		node *t2=new node();
		t2->ua=ub;
		t2->ub=ua;
		t2->cos=tcos;
		//ͷ�� 
		t2->next=p2->next;
		p2->next=t2;
		(p2->ua)++;
		
		count++;
		if(count%1000000==0)
			cout<<"reading:"<<count<<endl;
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
	node *p=mp[24570]->next;
	while(p)
	{
		cout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
		p=p->next;
	}
	cout<<"*************************************"<<endl;
	p=topn[24570];
	while(p)
	{
		cout<<p->ua<<" "<<p->ub<<" "<<p->cos<<endl;
		p=p->next;
	}
	
	writefile();
	
	return 0;
}
