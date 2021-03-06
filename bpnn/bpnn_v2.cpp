/*************************************************************************
	> File Name: bpnn.cpp
	> Author: tuzhuo
	> Mail: xmb028@163.com 
	> Created Time: Tue 21 Apr 2020 09:25:34 PM CST
 ************************************************************************/

//自己造轮子用全连接神经网络解决fizzbuzz问题 
//后续需要加上batch_normalization,L2正则化,多种SGD策略 

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
//以下超参数可以自己改变
const int N_data_length = 10;//输入数据的向量长度 
const int N_hidden_neuron = 600;//隐藏层神经元数目 
const int N_training_data = 400;//训练数据量 
const double random_rate = 15371.7;//自定义随机数种子 
const double lr = 0.0001;//学习率 
const int epoch = 2;//学习迭代次数 











//初始化weight参数函数 
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
		training_data_file<<i<<" ";
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











//神经元存储自己的参数 
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
	double get_output(int input[N_data_length])//N_data_length，即输入数据的维度决定了神经元参数向量的维度 
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
	void update_weight(double gradient[N_data_length])
	{
		for(int i=0;i<N_data_length;i++)
		{
			weight[i] -= lr * gradient[i];
		}
		
		return ;
		
	}
};

class hidden_layer{
private:
	int input_data_set[N_training_data][N_data_length];
	Neuron_hidden hidden_neurons[N_hidden_neuron];//隐藏层神经元 
public:
	hidden_layer(int intput_data[N_training_data][N_data_length])
	{
		//数据批量写入隐藏层的存储单元 
		for(int i=0;i<N_training_data;i++)
		{
			//Neuron_hidden[i].get_input(intput_data[i])
			for(int j=0;j<N_data_length;j++)
				this->input_data_set[i][j] = intput_data[i][j];
		}
	}
	void forward_propagation(double hidden_layer_outputs_data[N_training_data][N_hidden_neuron],bool save_parameters=false,bool save_hidden_outputs=false)
	{
		for(int i=0;i<N_training_data;i++)
		{
			for(int j=0;j<N_hidden_neuron;j++)
			{
				hidden_layer_outputs_data[i][j] = this->hidden_neurons[j].get_output(input_data_set[i]);//第i个数据交给第j个神经元计算 
			}
		}
		if(save_parameters)
			this->save_hidden_layer_parameters();
			
		if(save_hidden_outputs)
		{
			fstream hidden_layer_outputs("hidden_layer_outputs.csv", ios::out);
			for(int i=0;i<N_training_data;i++)//打印每个数据在每个神经元的输出 
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
	void backward_propagation(int data_index,double output_layer_gradients[4][N_hidden_neuron],bool save_gradient=false)
	{
		double hidden_layer_loss[N_hidden_neuron];
		for(int i=0;i<N_hidden_neuron;i++)
			hidden_layer_loss[i]=0;
		for(int i=0;i<N_hidden_neuron;i++)//输出层传播过来的梯度是4个输出神经元的计算结果
		{
			for(int j=0;j<4;j++)
			{
				hidden_layer_loss[i] += output_layer_gradients[j][i];//hidden_layer_loss=sum(output_layer_gradient)
			}
		}
		
		double hidden_layer_gradient[N_hidden_neuron][N_data_length];
		for(int i=0;i<N_hidden_neuron;i++)//求每个隐藏层神经元的参数梯度 
		{
			for(int j=0;j<N_data_length;j++)
			{
				hidden_layer_gradient[i][j] = hidden_layer_loss[i] * this->input_data_set[data_index][j];
			}
		}
		//更新每个隐藏层神经元的参数向量 
		for(int i=0;i<N_hidden_neuron;i++)
		{
			hidden_neurons[i].update_weight(hidden_layer_gradient[i]);
		}
		
		if(save_gradient)
		{
			fstream hidden_layer_gradient_file("hidden_layer_gradient.csv", ios::out);
			for(int i=0;i<N_hidden_neuron;i++)
			{
				for(int j=0;j<N_data_length;j++)
				{
					hidden_layer_gradient_file<<hidden_layer_gradient[i][j]<<" ";
				}
				hidden_layer_gradient_file<<endl;
			}
		}
		
		return ;
		
	}
	
	void save_hidden_layer_parameters()
	{
		fstream hidden_layer_parameters("hidden_layer_parameters.csv", ios::out);
		for(int i=0;i<N_hidden_neuron;i++)//打印所有神经元的参数向量 
		{
			for(int j = 0;j<N_data_length;j++)
			{
				hidden_layer_parameters<<hidden_neurons[i].get_weight_i(j)<<" ";
			}
			hidden_layer_parameters<<hidden_neurons[i].get_biase()<<endl;
		}
		return ;
	}
};











//之所以在这里将隐藏层和输出层分开来定义是因为c++不方便data.append()
class Neuron_output{
private:
	double weight[N_hidden_neuron];//隐藏层有多少个神经元，则输出层神经元的权重参数向量的维度就是多少 
	double biase;
public:
	Neuron_output()
	{
		for(int i=0;i<N_hidden_neuron;i++)
		{
			weight[i]=random(random_rate);
		}
		biase=random(random_rate);//31是质数 
		
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
		//后续激活应该使用softmax或者sigmoid函数 
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
	void update_weight(double gradient[N_hidden_neuron])
	{
		for(int i=0;i<N_hidden_neuron;i++)
		{
			weight[i] -= lr * gradient[i];
		}
		
		return ;
		
	}
};

class output_layer{
private:
	double input_data_set[N_training_data][N_hidden_neuron];//隐藏层的传过来的计算结果 
	Neuron_output output_neurons[4];//因为输出向量要求为维度为4，所以输出层神经元就4个就行了 
public:
	output_layer(double intput_data[N_training_data][N_hidden_neuron])//隐藏层每个神经元输出一个值 
	{
		//数据批量写入输出层的存储单元
		for(int i=0;i<N_training_data;i++)
			for(int j=0;j<N_hidden_neuron;j++)
			{
				this->input_data_set[i][j] = intput_data[i][j];
			}
	}
	void forward_propagation(double output_layer_outputs_data[N_training_data][4],bool softmax=false,bool save_parameters=false,bool save_outputs=false)
	{
		for(int i=0;i<N_training_data;i++)//循环计算每一个数据 
			for(int j=0;j<4;j++)
			{
				output_layer_outputs_data[i][j] = this->output_neurons[j].get_output(input_data_set[i]);//第i个数据交给第j个神经元计算
			}
			
		if(softmax)
		{
			for(int i=0;i<N_training_data;i++)//循环计算每一个数据每一维的softmax值 
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
			this->save_output_layer_parameters();
		
		if(save_outputs)
		{
			fstream output_layer_outputs("output_layer_outputs.csv", ios::out);
			for(int i=0;i<N_training_data;i++)//打印每个数据在每个神经元的输出 
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
	//使用均方误差做损失函数，这里的output_layer_outputs是已经被softmax过的 
	void predict_loss_function(int training_label[N_training_data][4],double output_layer_outputs[N_training_data][4],double loss[N_training_data][4],bool save_loss=false)
	{
		double sum=0;
		double each_data_total_loss[N_training_data];
		for(int i=0;i<N_training_data;i++)
		{
			for(int j=0;j<4;j++)
			{
				each_data_total_loss[i]+=pow(abs(training_label[i][j]-output_layer_outputs[i][j]),2);
				//loss[i][j] = abs(training_label[i][j]-output_layer_outputs[i][j]);
				loss[i][j] = training_label[i][j]-output_layer_outputs[i][j];
			}
			sum+=each_data_total_loss[i];
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
				loss_file<<" "<<each_data_total_loss[i]<<endl;
			}
		}
		
		return ;
		
	}
	double correct_rate(int training_label[N_training_data][4],double output_layer_outputs[N_training_data][4])
	{
		double count=0;
		for(int i=0;i<N_training_data;i++)
		{
			int index=0;
			for(int j=1;j<4;j++)
			{
				if(output_layer_outputs[i][j] > output_layer_outputs[i][index])//softmax回归 
				{
					index=j;
				}
			}
			if(training_label[i][index]==1)
				count++;
		}
		
		return count/N_training_data;
		
	}
	void backward_propagation(int data_index,double loss[4],double output_layer_gradients[4][N_hidden_neuron],bool save_gradient=false)
	{
		//暂时还不会对softmax求梯度...就用loss替代了 
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<N_hidden_neuron;j++)
			{
				output_layer_gradients[i][j] = loss[i] * this->input_data_set[data_index][j];
			}
		}
		//直接把本层的参数更新
		for(int i=0;i<4;i++)
		{
			output_neurons[i].update_weight(output_layer_gradients[i]);
		}
		if(save_gradient)
		{
			fstream output_layer_gradient("output_layer_gradient.csv", ios::out);
			for(int i=0;i<4;i++)
			{
				for(int j=0;j<N_hidden_neuron;j++)
				{
					output_layer_gradient<<output_layer_gradients[i][j]<<" ";
				}
				output_layer_gradient<<endl;
			}
		}
		
		return ;
		
	}
	
	void save_output_layer_parameters()
	{
		fstream output_layer_parameters("output_layer_parameters.csv", ios::out);
		for(int i=0;i<4;i++)//输出层只有4个神经元 
		{
			for(int j = 0;j<N_hidden_neuron;j++)
			{
				output_layer_parameters<<output_neurons[i].get_weight_i(j)<<" ";
			}
			output_layer_parameters<<output_neurons[i].get_biase()<<endl;
		}
		return ;
	}
};















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
	data_process(training_data,training_label,1/*数据起始点*/);
	save_training_data(training_data,training_label);
	
	hidden_layer *fizz_buzz_hidden_layer = new hidden_layer(training_data);
	double hidden_layer_outputs[N_training_data][N_hidden_neuron];
	fizz_buzz_hidden_layer -> forward_propagation(hidden_layer_outputs,true,true);
	
	output_layer *fizz_buzz_output_layer = new output_layer(hidden_layer_outputs);
	double output_layer_outputs[N_training_data][4];
	fizz_buzz_output_layer -> forward_propagation(output_layer_outputs,true,true,true);
	double loss[N_training_data][4];//此loss用于反向传播 
	fizz_buzz_output_layer -> predict_loss_function(training_label,output_layer_outputs,loss,true);
	cout<<"correct_rate : "<<fizz_buzz_output_layer -> correct_rate(training_label,output_layer_outputs)<<endl;
	
	//按照每个training data做反向传播、梯度下降、权重更新 
	for(int i=0;i<N_training_data;i++)
	{
		double output_layer_gradients[4][N_hidden_neuron];//每个输出层神经元的参数规模为[N_hidden_neuron]，仅保存输出层梯度即可，因为隐藏层不需要再反向传播了 
		fizz_buzz_output_layer -> backward_propagation(i,loss[i],output_layer_gradients,true);
		//输出层的梯度反向传播到隐藏层
		fizz_buzz_hidden_layer -> backward_propagation(i,output_layer_gradients,true);
	}
	
	//return 0;
	
	//training ! 
	for(int e=0;e<epoch;e++)
	{
		fizz_buzz_hidden_layer -> forward_propagation(hidden_layer_outputs,true,true);
		fizz_buzz_output_layer -> forward_propagation(output_layer_outputs,false,true,true);
		fizz_buzz_output_layer -> predict_loss_function(training_label,output_layer_outputs,loss,true);
		cout<<"correct_rate : "<<fizz_buzz_output_layer -> correct_rate(training_label,output_layer_outputs)<<endl;
		for(int i=0;i<N_training_data;i++)
		{
			double output_layer_gradients[4][N_hidden_neuron];//每个输出层神经元的参数规模为[N_hidden_neuron]，仅保存输出层梯度即可，因为隐藏层不需要再反向传播了 
			fizz_buzz_output_layer -> backward_propagation(i,loss[i],output_layer_gradients,true);
			//输出层的梯度反向传播到隐藏层
			fizz_buzz_hidden_layer -> backward_propagation(i,output_layer_gradients,true);
		}
	}
	
	return 0;
}
