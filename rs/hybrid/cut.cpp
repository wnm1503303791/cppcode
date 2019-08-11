/*
此代码作废，由linux下的命令：
split -b 560m at_cos.txt
代替执行 
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

fstream fout("at_cos_2.txt", ios::out);//打开文件，供写

int main()
{
	fstream in;
	in.open("at_cos.txt", ios::in);
	
	while(!in.eof())
	{
		long ua,ub;
		double fitness;
		in>>ua>>ub>>fitness;
		
		//if(ua%1000==0)
			cout<<ua<<endl;
		
		if(ua<=11727)
			continue ;
		else
			fout<<ua<<" "<<ub<<" "<<fitness;
	}
	
	return 0;
}
