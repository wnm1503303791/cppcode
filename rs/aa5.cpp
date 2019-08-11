/*
1、主要改进aa4源代码中n次调用read_data函数时间复杂度过高的问题。 
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

fstream fout("aa5_sort.txt", ios::out);//打开文件，供写

struct node
{
	long ua;
	long ub;
	long fitness;
	node *next;
};

node* mp[28703];

class individual_a_b
{
private:
	node *head_a;
	node *head_b;
	long NAME_A,NAME_B;
	double cos;
public:
	individual_a_b(long name_a,long name_b)
	{
		/*
		this->head_a=new node();
		if(head_a==NULL)
			cout<<"position 1:NO memory allocated!"<<endl;
		
		this->head_b=new node();
		if(head_b==NULL)
			cout<<"position 2:NO memory allocated!"<<endl;
		*/
		this->NAME_A=name_a;
		this->NAME_B=name_b;
		
		this->head_a=(mp[name_a]);
		this->head_b=(mp[name_b]);
		
		this->cos=0;
	}
	
	
	
	
	//read data_a
	/*
	bool read_data_a()
	{
		fstream infile;
		infile.open("AA.txt", ios::in);
		
		node *p=this->head_a;
		
		while(!infile.eof())
		{
			long ua,ub,fitness;
			infile>>ua>>ub>>fitness;
			if(ua==this->NAME_A)
			{
				node *t=new node();
				t->ua=ua;
				t->ub=ub;
				t->fitness=fitness;
				
				p->next=t;
				p=p->next;
			}
			if(ua>this->NAME_A)
				return true;
		}

		return true;
	}
	//read data_b
	bool read_data_b()
	{
		fstream infile;
		infile.open("AA.txt", ios::in);
		
		node *p=this->head_b;
		
		while(!infile.eof())
		{
			long ua,ub,fitness;
			infile>>ua>>ub>>fitness;
			if(ua==this->NAME_B)
			{
				node *t=new node();
				t->ua=ua;
				t->ub=ub;
				t->fitness=fitness;
				
				p->next=t;
				p=p->next;
			}
			if(ua>this->NAME_B)
				return true;
		}

		return true;
	}
	*/
	
	
	
	
	//viewing
	bool display()
	{
		node *p1=this->head_a->next;
		while(p1)
		{
			cout<<p1->ua<<" ";
			cout<<p1->ub<<" ";
			cout<<p1->fitness<<endl;
			p1=p1->next;
		}
		
		node *p2=this->head_b->next;
		while(p2)
		{
			cout<<p2->ua<<" ";
			cout<<p2->ub<<" ";
			cout<<p2->fitness<<endl;
			p2=p2->next;
		}
		
		return true;
	}
	//calculate cos
	bool calculate()
	{
		double sum=0;
		double ua2=0;
		double ub2=0;
		
		node *p1=this->head_a->next;
		node *p2=this->head_b->next;
		/*
		while(p1)
		{
			while(p2)
			{
				if(p1->ub==p2->ub)
				{
					sum+=(p1->fitness)*(p2->fitness);
					goto A;
				}
				
				p2=p2->next;
			}
			
			A:p1=p1->next;
			p2=this->head_b->next;
		}
		*/
		int *flag=(int *)malloc(28703*sizeof(int));
		int *fit=(int *)malloc(28703*sizeof(int));
		
		for(int i=1;i<28703;i++)
		{
			flag[i]=0;
			fit[i]=0;
		}
		while(p1)
		{
			flag[(p1->ub)]=1;
			fit[(p1->ub)]=p1->fitness;
			p1=p1->next;
		}
		while(p2)
		{
			if(flag[(p2->ub)]!=0)
				sum+=fit[(p2->ub)]*(p2->fitness);
			p2=p2->next;
		}
		
		free(flag);//important!
		free(fit);//important!
		
		if(sum<=eps)
		{
			this->cos=0;
			return true;
		}
		
		p1=this->head_a->next;
		while(p1)
		{
			ua2+=(p1->fitness)*(p1->fitness);
			p1=p1->next;
		}
		
		p2=this->head_b->next;
		while(p2)
		{
			ub2+=(p2->fitness)*(p2->fitness);
			p2=p2->next;
		}
		
		this->cos=sum/(sqrt(ua2)*sqrt(ub2));
		
		return true;
	}
	//writing file
	bool write_cos()
	{
		if(this->cos<=eps)
			return false; 
		
		fout<<this->NAME_A<<" "<<this->NAME_B<<" "<<this->cos<<endl;
		return true;
	}
};

//读入算法现在已是线性时间复杂度 
bool read_data()
{
	fstream infile;
	infile.open("AA.txt", ios::in);
	/*
	mp[name]=new node();
	node *p=(mp[name]);
	*/
	node *p;
	long current_name=0;
	
	while(!infile.eof())
	{
		long ua,ub,fitness;
		infile>>ua>>ub>>fitness;
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
			t->fitness=fitness;
				
			p->next=t;
			p=p->next;
		}
	}

	return true;
}


int main()
{
	/*
	individual_a_b *obj=new individual_a_b(1,2);
	obj->read_data_a();
	obj->read_data_b();
	obj->display();
	obj->calculate();
	obj->write_cos();
	*/
	/* 
	for(int i=1;i<=28702;i++)
	{
		if(read_data(i))
			cout<<"reading over:"<<i<<endl;
	}
	*/
	for(int i=1;i<=28702;i++)
		mp[i]=new node();
	
	if(read_data())
		cout<<"read data over!"<<endl;
	
	//for(int i=1;i<=28702;i++)
	for(int i=28702;i>=1;i--)
		for(int j=i+1;j<=28702;j++)
		{
			individual_a_b *obj=new individual_a_b(i,j);
			//obj->read_data_a();
			//obj->read_data_b();
			//obj->display();
			obj->calculate();
			obj->write_cos();
			
			cout<<"finished:"<<i<<" "<<j<<endl;
			
			delete obj;
		}
	
	
	/*
	//最小时间复杂度测试代码
	for(int i=1;i<=28702;i++)
		for(int j=i+1;j<=28702;j++)
		{
			cout<<i<<" "<<j<<endl;
		}
	*/
	
	return 0;
}
