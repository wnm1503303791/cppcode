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
const int INF = 1000000000;
const int maxn = 100;
int T,n,m;

int main(int count, char* input_parameters[])
{
	for(int i=1;i<count;i++)
        cout<<i<<":"<<input_parameters[i]<<endl;
        
    const char *fname1 = input_parameters[1];
    const char *fname2 = input_parameters[2];
    const char *fname3 = input_parameters[3];
    const char *fname4 = input_parameters[4];
	
    fstream infile1(fname1, ios::in);//read file
	fstream infile2(fname2, ios::in);//read file
	fstream infile3(fname3, ios::in);//read file
	fstream outfile(fname4, ios::out);//write file
	
    //return 0;

    ll index=0;
	string flag="chr00";
	while(!infile1.eof() && !infile2.eof() && !infile3.eof() )
	{
        index++;

        //cut file 1
		string GeneSymbol1,GeneName1;
        long num1,l1,ex1;
        infile1>>GeneSymbol1>>GeneName1>>num1>>l1>>ex1;

        //cut file 2
		string GeneSymbol2,GeneName2;
        long num2,l2,ex2;
        infile2>>GeneSymbol2>>GeneName2>>num2>>l2>>ex2;

        //gfold file
        string GeneSymbol3,GeneName3;
		double gfold,w1,w2,w3,w4;
        infile3>>GeneSymbol3>>GeneName3>>gfold>>w1>>w2>>w3>>w4;

        //if(flag.compare(GeneSymbol.substr(0,5)))//compare不等的结果会输出1
		if( ! GeneSymbol1.compare(GeneSymbol3) )//compare不等的结果会输出1
		{
            outfile<<GeneSymbol3<<'\t'<<GeneName3<<'\t'<<abs(num1-num2)*abs(gfold)<<endl;
		}
		else
		{
			cout<<"ERROR at : "<<index<<" ; "<<GeneSymbol1<<'\t'<<GeneSymbol3<<endl;
		}
	}

    infile1.close();
    infile2.close();
    infile3.close();
    outfile.close();

    return 0;
}
