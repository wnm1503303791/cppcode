/*************************************************************************
	> File Name: bpnn.cpp
	> Author: tuzhuo
	> Mail: xmb028@163.com 
	> Created Time: Tue 21 Apr 2020 09:25:34 PM CST
 ************************************************************************/

//�Լ���������ȫ������������fizzbuzz���� 

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
#include<time.h>
using namespace std;

typedef long long ll;
const double PI = acos(-1.0);
const double eps = 1e-6;
const int INF = 1000000000;
const int maxn = 100;
int T,n,m;
//���³����������Լ��ı�
const int N_data_length = 10;//�������ݵ��������� 
const int N_hidden_neuron = 600;//���ز���Ԫ��Ŀ 
const int N_training_data = 400;
const double random_rate = 15351.7;//�Զ������������ 
const double lr = 0.00001;











//��ʼ��weight�������� 
double random(double range)
{
	/*
	srand(time(0));
	return (((rand() / (double)(end-start)) - 2.0)/(end-start)+start)/1000;
	*/
    return rand()/range - 1;

}

void data_process(int source_data[N_training_data][N_data_length],int label[N_training_data][4],long start)
{
	for(int i = 0 ; i < N_training_data ; i++)
	{
		long t = start+i;
		for(int j=0 ; j<N_data_length ; j++)
		{
			source_data[i][N_data_length-j-1] = t%2;
			t=t/2;
		}
		t = start+i;
		//make label lists
		if(t%3==0&&t%5==0)
		{
			//{0,0,0,1}
			label[i][0]=0;
			label[i][1]=0;
			label[i][2]=0;
			label[i][3]=1;
		}
		else if(t%3==0)
		{
			label[i][0]=0;
			label[i][1]=1;
			label[i][2]=0;
			label[i][3]=0;
		}
		else if(t%5==0)
		{
			label[i][0]=0;
			label[i][1]=0;
			label[i][2]=1;
			label[i][3]=0;
		}
		else
		{
			label[i][0]=1;
			label[i][1]=0;
			label[i][2]=0;
			label[i][3]=0;
		}
	}
	
	return ;

}

void save_training_data(int source_data[N_training_data][N_data_length],int label[N_training_data][4])
{
	//save datas as file
	fstream training_data_file("training_data.csv", ios::out);
	for(int i=0;i<N_training_data;i++)
	{
		training_data_file<<i+i<<" ";
		for(int j=0;j<N_data_length;j++)
		{
			training_data_file<<source_data[i][j];
		}
		training_data_file<<" ";
		for(int j=0;j<4;j++)
		{
			training_data_file<<label[i][j];
		}
		training_data_file<<endl;
	}
	
	return ;
	
}











//��Ԫ�洢�Լ��Ĳ��� 
class Neuron_hidden{
private:
	double weight[N_data_length];
	double biase;
public:
	Neuron_hidden()
	{
		for(int i=0;i<N_data_length;i++)
		{
			weight[i]=random(random_rate);
		}
		biase=random(random_rate);
		
		return ;
		
	}
	double get_output(int input[N_data_length])//N_data_length�����������ݵ�ά�Ⱦ�������Ԫ����������ά�� 
	{
		double result = 0;
		for(int i=0;i<N_data_length;i++)
		{
			result += input[i] * this->weight[i];
		}
		result+=this->biase;
		//ReLU
		if(result > eps)
			return result;
		else
			return 0;
	}
	double get_weight_i(int i)
	{
		return weight[i];
	}
	double get_biase()
	{
		return biase;
	}
};

class hidden_layer{
private:
	int input_data_set[N_training_data][N_data_length];
	Neuron_hidden hidden_neurons[N_hidden_neuron];//���ز���Ԫ 
public:
	hidden_layer(int intput_data[N_training_data][N_data_length])
	{
		//��������д�����ز�Ĵ洢��Ԫ 
		for(int i=0;i<N_training_data;i++)
		{
			//Neuron_hidden[i].get_input(intput_data[i])
			for(int j=0;j<N_data_length;j++)
				this->input_data_set[i][j] = intput_data[i][j];
		}
	}
	void forward_propagation(double hidden_layer_outputs_data[N_training_data][N_hidden_neuron],bool save_parameters=false)
	{
		for(int i=0;i<N_training_data;i++)
		{
			for(int j=0;j<N_hidden_neuron;j++)
			{
				hidden_layer_outputs_data[i][j] = this->hidden_neurons[j].get_output(input_data_set[i]);//��i�����ݽ�����j����Ԫ���� 
			}
		}
		if(save_parameters)
		{
			fstream hidden_layer_parameters("hidden_layer_parameters.csv", ios::out);
			for(int i=0;i<N_hidden_neuron;i++)//��ӡ������Ԫ�Ĳ������� 
			{
				for(int j = 0;j<N_data_length;j++)
				{
					hidden_layer_parameters<<hidden_neurons[i].get_weight_i(j)<<" ";
				}
				hidden_layer_parameters<<hidden_neurons[i].get_biase()<<endl;
			}
			
			fstream hidden_layer_outputs("hidden_layer_outputs.csv", ios::out);
			for(int i=0;i<N_training_data;i++)//��ӡÿ��������ÿ����Ԫ����� 
			{
				for(int j=0;j<N_hidden_neuron;j++)
				{
					hidden_layer_outputs<<hidden_layer_outputs_data[i][j] <<" ";
				}
				hidden_layer_outputs<<endl;
			}
		}
		
		return ;
		
	}
};









//֮���������ｫ���ز�������ֿ�����������Ϊc++������data.append()
class Neuron_output{
private:
	double weight[N_hidden_neuron];
	double biase;
public:
	Neuron_output()
	{
		for(int i=0;i<N_hidden_neuron;i++)
		{
			weight[i]=random(random_rate);
		}
		biase=random(random_rate);//31������ 
		
		return ;
		
	}
	double get_output(double input[N_hidden_neuron])
	{
		double result = 0;
		for(int i=0;i<N_hidden_neuron;i++)
		{
			result += input[i] * this->weight[i];
		}
		result+=this->biase;
		//ReLU
		//��������Ӧ��ʹ��softmax����sigmoid���� 
		if(result > eps)
			return result;
		else
			return 0;
	}
	double get_weight_i(int i)
	{
		return weight[i];
	}
	double get_biase()
	{
		return biase;
	}
};

class output_layer{
private:
	double input_data_set[N_training_data][N_hidden_neuron];//���ز�Ĵ������ļ����� 
	Neuron_output output_neurons[4];//��Ϊ�������Ҫ��Ϊά��Ϊ4�������������Ԫ��4�������� 
public:
	output_layer(double intput_data[N_training_data][N_hidden_neuron])//���ز�ÿ����Ԫ���һ��ֵ 
	{
		//��������д�������Ĵ洢��Ԫ
		for(int i=0;i<N_training_data;i++)
			for(int j=0;j<N_hidden_neuron;j++)
			{
				this->input_data_set[i][j] = intput_data[i][j];
			}
	}
	void forward_propagation(double output_layer_outputs_data[N_training_data][4],bool softmax=false,bool save_parameters=false)
	{
		for(int i=0;i<N_training_data;i++)//ѭ������ÿһ������ 
			for(int j=0;j<4;j++)
			{
				output_layer_outputs_data[i][j] = this->output_neurons[j].get_output(input_data_set[i]);//��i�����ݽ�����j����Ԫ����
			}
			
		if(softmax)
		{
			for(int i=0;i<N_training_data;i++)//ѭ������ÿһ������ÿһά��softmaxֵ 
			{
				double sum=0;
				for(int j=0;j<4;j++)
				{
					sum+=exp(output_layer_outputs_data[i][j]);
				}
				for(int j=0;j<4;j++)
				{
					output_layer_outputs_data[i][j] = exp(output_layer_outputs_data[i][j])/sum;
				}
			}
		}
			
		if(save_parameters)
		{
			fstream output_layer_parameters("output_layer_parameters.csv", ios::out);
			for(int i=0;i<4;i++)//�����ֻ��4����Ԫ 
			{
				for(int j = 0;j<N_hidden_neuron;j++)
				{
					output_layer_parameters<<output_neurons[i].get_weight_i(j)<<" ";
				}
				output_layer_parameters<<output_neurons[i].get_biase()<<endl;
			}
			
			fstream output_layer_outputs("output_layer_outputs.csv", ios::out);
			for(int i=0;i<N_training_data;i++)//��ӡÿ��������ÿ����Ԫ����� 
			{
				output_layer_outputs<<1+i<<" ";
				for(int j=0;j<4;j++)
				{
					output_layer_outputs<<" "<< output_layer_outputs_data[i][j] <<" ";
				}
				output_layer_outputs<<endl;
			}
		}
		
		return ;
		
	}
	//ʹ�þ����������ʧ�����������output_layer_outputs���Ѿ���softmax���� 
	void predict_loss_function(int training_label[N_training_data][4],double output_layer_outputs[N_training_data][4],double loss[N_training_data],bool save_loss=false)
	{
		double sum=0;
		for(int i=0;i<N_training_data;i++)
		{
			for(int j=0;j<4;j++)
			{
				loss[i]+=pow(abs(training_label[i][j]-output_layer_outputs[i][j]),2);
			}
			sum+=loss[i];
		}
		cout<<"total loss in this epoch is : "<<sum<<endl;
		
		if(save_loss)
		{
			fstream loss_file("loss.csv", ios::out);
			for(int i=0;i<N_training_data;i++)
			{
				loss_file<<1+i<<" ";
				for(int j=0;j<4;j++)
				{
					loss_file<<training_label[i][j];
					if(j<3)
						loss_file<<",";
				}
				loss_file<<" ";
				for(int j=0;j<4;j++)
				{
					loss_file<<output_layer_outputs[i][j];
					if(j<3)
						loss_file<<",";
				}
				loss_file<<" "<<loss[i]<<endl;
			}
		}
		
		return ;
	}
};







double correct_rate(int training_label[N_training_data][4],double output_layer_outputs[N_training_data][4])
{
	double count=0;
	for(int i=0;i<N_training_data;i++)
	{
		int index=0;
		for(int j=1;j<4;j++)
		{
			if(output_layer_outputs[i][j] > output_layer_outputs[i][index])//softmax�ع� 
			{
				index=j;
			}
		}
		if(training_label[i][index]==1)
			count++;
	}
	return count/N_training_data;
}









int main()
{	
	/*
	for(int i=0;i<10;i++)
	{
		cout<<random(random_rate)<<endl;
	}
	*/
	int training_data[N_training_data][N_data_length];
	int training_label[N_training_data][4];//[0,fizz,buzz,fizzbuzz]
	data_process(training_data,training_label,1/*������ʼ��*/);
	save_training_data(training_data,training_label);
	
	hidden_layer *fizz_buzz_hidden_layer = new hidden_layer(training_data);
	double hidden_layer_outputs[N_training_data][N_hidden_neuron];
	fizz_buzz_hidden_layer->forward_propagation(hidden_layer_outputs,true);
	
	output_layer *fizz_buzz_output_layer = new output_layer(hidden_layer_outputs);
	double output_layer_outputs[N_training_data][4];
	fizz_buzz_output_layer->forward_propagation(output_layer_outputs,true,true);
	double loss[N_training_data];
	fizz_buzz_output_layer->predict_loss_function(training_label,output_layer_outputs,loss,true);
	
	cout<<"correct_rate : "<<correct_rate(training_label,output_layer_outputs)<<endl;
	
	return 0;
}
