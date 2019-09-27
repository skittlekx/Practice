#pragma once
#include <vector>
#include <iostream>
#include <map>
//神经元定义
class Perceptron
{
	double(*activator)(double);
	int num_input;//输入参数个数
	int num_output;//输出参数个数
	
	double** weights;//权重矩阵  [no:ni]
	double* bias; //偏置(列)向量     [no]
	double** w_b; //[no:ni+1]

public:
	//Perceptron();
	Perceptron(double(*f)(double), int in = 2, int out = 1);
	~Perceptron();

	void print();
	std::vector<double> predict(std::vector<double>);
	void train(double* dataVec, double* lables, int dataLen, int iteration, double lr);
	double _one_iteration(double** indata, double** lables, int dataLen, double lr);
	double update_weight(std::vector<double>, std::vector<double>, std::vector<double>, double);
};

