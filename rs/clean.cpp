/* 
此插件清除pianhao.exe筛选出来的结果中的所有0行 
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
	
//fstream fout("sort.txt", ios::out);//打开文件，供写 

class cleaner{
private:
	long realnum,counter;
public:
	cleaner()
	{
		realnum=0;
		counter=0;
	}
	//main function
	bool cleaning(fstream &infile,fstream &outfile)
	{
		long a,b,c;
		while(!infile.eof())
		{
			realnum++;
			infile>>a>>b>>c;
			if(a>0)
			{
				counter++;
				outfile<<a<<" "<<b<<" "<<c<<endl;
			}
			else
				continue;
		}
		return true;
	}
	bool display()
	{
		cout<<"real:"<<realnum<<endl<<"result:"<<counter<<endl;
		return true;
	}
};

int main()
{
	fstream f1;
    f1.open("sort20.txt", ios::in);
    fstream f2("clean20.txt", ios::out);
    
    cleaner *obj=new cleaner();
    if(obj->cleaning(f1,f2)&&obj->display())
    	delete obj;
    
	return 0;
}
