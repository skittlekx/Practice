// NetWork.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Perceptron.h"
#include <vector>
using namespace std;
double fun(double x)
{
	return x > 0 ? 1 : 0;
}
int main()
{
	Perceptron pc(fun);
	double _in[] = {1,1,1,0,0,0,0,1};
	double _la[] = {1,0,0,0};
	cout << "---------train----------" << endl;
	pc.train(_in, _la, 4, 10, 0.1);
	//pc.print();
	cout << "---------test----------" << endl;
	for (int i = 0; i < 7; i++) {
		std::vector<double> test;
		test.push_back(_in[i]);
		test.push_back(_in[i+1]);
		cout << _in[i] << " and " << _in[i + 1] << " = " << pc.predict(test)[0] << endl;
	}
	
}

