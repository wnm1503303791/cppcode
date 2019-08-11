/*
�˳�����ݵڶ���������aa��rs������������Ҫ����author_label.txt�ж����Ƽ���5������û����Ƿ������û���ͬlabel���û���
ֻҪ5������һ�����У����϶����û����Ƽ�ϵͳ���С�
�ر�Ҫָ����������ͬ�ڵ�һ��ʹ�õ�evaluation���۷������˴���ʹ�ù�ʽF-Score=(2*P*R)/(P+R)��������
top N�е�NΪ�Ƽ��ĸ�����P��ʾN��������������N��R��ʾN��������������������ͬlabel
F-Score��ȡֵΪ0��1֮���С�� 
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

fstream fout("embed_rs_evaluation.md", ios::out);//���ļ�����д

struct node
{
	long ua;
	long ub;
	double cos;
	node *next;
};

int dict[28703];//��¼�����û���label 
node* mp[28703];
int labelnum[5];//��¼����label�ֱ��е��������� 

ll read_data()
{
	fstream infile;
	infile.open("embed_rs.txt", ios::in);
	
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
			//cout<<"reading:"<<current_name<<endl;
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
	
	for(int i=1;i<=28702;i++)//����δ��author_label.txt�н��б�ע���û�����label��Ϊ0����ʾ����� 
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
		if(dict[i]<=0)
			continue;
		//ѭ�����ڽ����һ���û�����F-Score���� 
		ll target=0;
		node *p=mp[i]->next;
		while(p)
		{
			if(dict[(p->ub)]==dict[i])
				target++;
			p=p->next;
		}
		double pc=(double)target/(mp[i]->ua);
		double r=(double)target/labelnum[dict[i]];
		double f=(2*pc*r)/(pc+r);
		
		if(pc>eps)
			fout<<i<<" "<<pc<<" "<<r<<" "<<f*1000<<endl;
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
	
	long counter=-1;
	double sum=0;
	fstream in;
	in.open("embed_rs_evaluation.md", ios::in);
	while(!in.eof())
	{
		long usr;
		double p,r,f;
		in>>usr>>p>>r>>f;
		counter++;
		sum+=f;
	}
	fout<<counter<<" "<<sum<<" "<<sum/counter<<endl;
	
	return 0;
}
