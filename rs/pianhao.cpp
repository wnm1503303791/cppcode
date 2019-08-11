/*
初步筛选程序，对于AT.txt中的每个A，筛出其T中fitness值最高的20个，若不足20个则用0行填充。 
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
	
fstream fout("sort.txt", ios::out);//打开文件，供写 

struct node
{
	long name;
	long term;
	long fitness;
	node *next;
};



class data_set
{
private:
	node *top;
	int current_num;
	int max;
public:
	data_set(long n)
	{
		top=(node *)malloc(n*sizeof(node));
		if(top==NULL)
			cout<<"position 2:NO memory allocated!"<<endl;
			
		this->current_num=0;
		this->max=n;
	}
	//add fuction
	bool add(node *t)
	{
		if(current_num<=max)
		{
			top[current_num].name=t->name;
			top[current_num].term=t->term;
			top[current_num].fitness=t->fitness;
			current_num++;
		}
		else
		{
			//找出目前最小的并替掉它 
			//此段代码可以通过使用排序算法重构掉，但是此举会增加时间复杂度 
			long min=top[0].fitness;
			long key=0;
			for(int i=0;i<max;i++)
			{
				if(top[i].fitness<min)
				{
					key=i;
					min=top[i].fitness;
				}
			}
			
			if(t->fitness>min)
			{
				top[key].name=t->name;
				top[key].term=t->term;
				top[key].fitness=t->fitness;
			}
		}
	}
	//交换top[a]与top[b]
	bool exchange(int a,int b)
	{
		long t_name,t_term,t_fitness;
		
		t_name=top[a].name;
		t_term=top[a].term;
		t_fitness=top[a].fitness;
		
		top[a].name=top[b].name;
		top[a].term=top[b].term;
		top[a].fitness=top[b].fitness;
		
		top[b].name=t_name;
		top[b].term=t_term;
		top[b].fitness=t_fitness;
		
		return true;
	}
	//sort
	bool select_sort()
	{
		int MAX=this->max;
		if(this->current_num<max)
			MAX=this->current_num;
		for(int i=0;i<MAX;i++)
		{
			long min=top[i].fitness;
			long key=i;
			for(int j=i+1;j<MAX;j++)
			{
				if(top[j].fitness<min)
				{
					key=j;
					min=top[j].fitness;
				}
			}
			this->exchange(i,key);
		}
		
		return true;
	}
	//view
	bool view_data()
	{
		this->select_sort();
		for(int i=0;i<max;i++)
		{
			cout<<top[i].name<<" "<<top[i].term<<" "<<top[i].fitness<<endl;
		}
		return true;
	}
	//写入文件函数 
	bool write_file()
	{
		this->select_sort();
		for(int i=0;i<max;i++)
		{
			fout<<top[i].name<<" "<<top[i].term<<" "<<top[i].fitness<<endl;
		}
		return true;
	}
};



class individual
{
private:
	node *head=NULL;
	data_set *top10;
	long num;
public:
	individual(long n=10)
	{
		head=new node();
		if(head==NULL)
			cout<<"position 1:NO memory allocated!"<<endl;
		num=0;
		top10=new data_set(n);
	}
	//read all related data
	bool read_data(fstream &infile,long NAME)
	{
		long name,term,fitness;
		node *p=head;
		while(!infile.eof())
		{
			infile>>name>>term>>fitness;
			//cout<<name<<" "<<term<<" "<<fitness<<endl;
			if(name==NAME)
			{
				num++;
				node *t=new node();
				t->name=name;
				t->term=term;
				t->fitness=fitness;
				p->next=t;
				p=p->next;
			}
		}
		
		return true;
	}
	//view the Bignode datalink;
	bool view_data()
	{
		node *p=head->next;
		while(p)
		{
			cout<<p->name<<","<<p->term<<","<<p->fitness<<endl;
			p=p->next;
		}
		return true;
	}
	//find top 10
	bool collect10()
	{
		node *p=head->next;
		while(p)
		{
			top10->add(p);
			p=p->next;
		}
		top10->view_data();
		top10->write_file();
		return true;
	}
};



int main()
{
	for(int i=1;i<=28702;i++)
	{
		fstream f1;
    	f1.open("AT.txt", ios::in);//打开数据集,供读
		
		individual *obj=new individual(20);
		obj->read_data(f1,i);
		//obj->view_data();
		obj->collect10();
		delete obj;
	}
	/*
	individual *obj1=new individual(20);
	obj1->read_data(f1,1);
	//obj->view_data();
	obj1->collect10();
	
	individual *obj2=new individual(20);
	obj2->read_data(f1,2);
	//obj->view_data();
	obj2->collect10();
	*/
	return 0;
}
