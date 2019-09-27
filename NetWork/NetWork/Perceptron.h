#pragma once
#include <vector>
#include <iostream>
#include <map>
//��Ԫ����
class Perceptron
{
	double(*activator)(double);
	int num_input;//�����������
	int num_output;//�����������
	
	double** weights;//Ȩ�ؾ���  [no:ni]
	double* bias; //ƫ��(��)����     [no]
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

