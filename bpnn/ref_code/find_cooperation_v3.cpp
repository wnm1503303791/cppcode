/*************************************************************************
	> File Name: make-yj-list.cpp
	> Author: tuzhuo
	> Mail: xmb028@163.com 
	> Created Time: Wed 13 Nov 2019 08:27:36 PM CST
 ************************************************************************/

/*
你可不可以再做一件事，就是：
比较（0000000001 + 0000000010 - 2 * 0000000000)与（0000000011 - 0000000000)，诸如此类
就是说，如果我们有0000000000、0000000001、0000000010、0000000100、...等，是否可以直接算出变异组合的效应

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
const int INF = 1000000000;
const int maxn = 100;
int T,n,m;


void sorted()
{
	//fstream infile("../1024seqs/1024_seqs_summary.csv", ios::in);//read file
	fstream infile("1024_seqs_summary.csv", ios::in);//read file
	fstream outfile("1024_seqs_summary_filted.csv", ios::out);//write file
	int index=1;
    while(!infile.eof() && index<=1024)
    {
    	string line,seqs,data;
    	infile>>line>>seqs>>data;
    	outfile<<seqs.substr(11,10)<<'\t'<<data.substr(9,5)<<endl;
        index++;
	}
}

void identify()
{
	fstream infile("1024_seqs_summary_filted.csv", ios::in);//write file
	fstream outfile("cascade_vs_direct.csv", ios::out);//write file
	struct node{
		string id;
		double score;
	};
	
	node data[1024];
	int index=0;
	while(!infile.eof())
	{
		infile>>data[index].id>>data[index].score;
		index++;
	}
    
    outfile<<"id"<<','<<"cascade_score"<<','<<"direct_score"<<endl;
	long hash[10]={1,2,4,8,16,32,64,128,256,512};
	
	for(int i=0;i<1024;i++)
	{
		int a,A[10];
		int n=10;
		a=i;
        for(int j=1;j<=n;j++)
		{
			A[j-1]=a%2;
			a=a/2;
		}
		/*
		for(int j=1;j<=n;j++)
		{
			if(A[j-1]==1)
				cout<<hash[j-1]<<',';
		}
		cout<<endl;
		*/
		int count=0;
		double sum=0;
		for(int j=1;j<=n;j++)
		{
			if(A[j-1]==1)
			{
				sum+=data[hash[j-1]].score;
				count++;
			}
		}
		
		double cascade_score,direct_score;
		cascade_score = sum - count*(data[0].score);
		direct_score = data[i].score - data[0].score;
		
		outfile<<"id_"<<data[i].id<<','<<cascade_score<<','<<direct_score<<endl;
	}
	/*
	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
		{
			if (i==j)
			{
				continue;
			}
			
			
			if(data[0].score>data[hash[i]].score && data[hash[i]+hash[j]].score>data[hash[j]].score)
			{
				outfile<<data[0].id<<'\t'<<data[0].score<<endl;
				outfile<<data[hash[i]].id<<'\t'<<data[hash[i]].score<<endl;
				outfile<<data[hash[j]].id<<'\t'<<data[hash[j]].score<<endl;
				outfile<<data[hash[i]+hash[j]].id<<'\t'<<data[hash[i]+hash[j]].score<<endl<<endl;
			}
			
			if(data[0].score>data[hash[j]].score && data[hash[i]+hash[j]].score>data[hash[i]].score)
			{
				outfile<<data[0].id<<'\t'<<data[0].score<<endl;
				outfile<<data[hash[i]].id<<'\t'<<data[hash[i]].score<<endl;
				outfile<<data[hash[j]].id<<'\t'<<data[hash[j]].score<<endl;
				outfile<<data[hash[i]+hash[j]].id<<'\t'<<data[hash[i]+hash[j]].score<<endl<<endl;
			}
			
			
            for(int k1=0;k1<1024;k1++)
            {
                if(data[k1].id[9-i]=='1' || data[k1].id[9-j]=='1')
                {
                	//cout<<data[k1].id<<endl;
                    continue;
                }

			    outfile<<"id_"<<data[k1].id<<','<<data[k1].score<<',';
			    outfile<<"id_"<<data[hash[i]+k1].id<<','<<data[hash[i]+k1].score<<',';
			    outfile<<"id_"<<data[hash[j]+k1].id<<','<<data[hash[j]+k1].score<<',';
			    outfile<<"id_"<<data[hash[i]+hash[j]+k1].id<<','<<data[hash[i]+hash[j]+k1].score<<endl;
            }
		}
	*/
}

int main()
{
	/*
	int count=1;
    while(!infile.eof())
    {
    	string gene,chrom,start,end;
        infile>>gene>>chrom>>start>>end;
        outfile<<"mkdir "<<count<<"_"<<gene<<endl;
        outfile<<"CUDA_VISIBLE_DEVICES=0 python /public/home/ztu/projects/basenji-old/relatedcode/nxiepo/draw/basenji_sat_region_tz_2.py -f /public/home/ztu/projects/nxiepo/data/rice_all_genomes_v7.fasta -o "<<count<<"_"<<gene<<" -t formal_154_list.txt /public/home/ztu/projects/lcming/first/models/first/mlc_154_first_params.txt /public/home/ztu/projects/lcming/first/models/first/model_best.tf "<<chrom<<" "<<start<<" "<<end<<" C171_q30 W208_q30 C089_q30 C195_q30 W296_q30 C065_q30 W026_q30 W309_q30 C076_q30 W265_q30 W147_q30 C175_q30 W145_q30 C078_q30"<<endl;
        outfile<<"zip -r "<<count<<"_"<<gene<<".zip "<<count<<"_"<<gene<<endl<<endl;
        
		count++;
    }
    cout<<count-1<<endl;
    */
	sorted();
	identify();
    
	return 0;
}
