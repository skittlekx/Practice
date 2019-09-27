#include "pch.h"
#include "Perceptron.h"
using namespace std;

//Perceptron::Perceptron()
//{
//}

Perceptron::Perceptron(double(*f)(double), int in, int out):
	activator(f),
	num_input(in),
	num_output(out)
{
	weights = new double*[out];
	w_b = new double*[out];
	bias = new double[out];
	for (int i = 0; i < out; i++) {
		weights[i] = new double[in];
		w_b[i] = new double[in + 1];
		memset(weights[i], 0.0l, in * sizeof(double));
		memset(w_b[i], 0.0l, (in + 1) * sizeof(double));
	}
	memset(bias, 0.0l, out * sizeof(double));
}


Perceptron::~Perceptron()
{
}

void Perceptron::print() {
	int i = 0;
	/*cout << "w ";
	int t = num_output;
	while (t-- > 0) cout << "  ";
	cout << "| b" << endl;*/
	for (int i = 0; i < num_output; i++) {
		cout << "weights:[ ";
		for (int j = 0; j < num_input-1; j++) {
			cout << weights[i][j] << ", ";
		}
		cout << weights[i][num_input - 1] << "]\nbias: " << bias[i] << endl;
	}
}
vector<double> Perceptron::predict(vector<double> indata) {
	vector<double>res;
	res.resize(num_output);
	for (int i = 0; i < num_output; i++) {
		double temp = 0;
		for (int j = 0; j < num_input; j++) {
			temp += indata[j] * weights[i][j];
		}
		res[i] = activator(temp + bias[i]);
	}
	return res;
}
void Perceptron::train(double* dataVec,double* lables, int dataLen,int iteration,double lr) {
	double **inData = new double*[dataLen];
	double **labData = new double*[dataLen];
	int ki = 0 , kl = 0;
	for (int i = 0; i < dataLen; i++) {
		inData[i] = new double[num_input];
		labData[i] = new double[num_output];
		for (int j = 0; j < num_input; j++) {
			inData[i][j] = dataVec[ki++];
		}
		for (int j = 0; j < num_output; j++) {
			labData[i][j] = lables[kl++];
		}
	}
	//-------------------
	cout << "train data:" << endl;
	for (int i = 0; i < dataLen; i++) {
		for (int j = 0; j < num_input; j++) {
			cout << inData[i][j] << ' ';
		}
		for (int j = 0; j < num_output; j++) {
			cout << labData[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	//-------------------
	for (int i = 0; i < iteration; i++) {
		cout << "iteration " << i << " : Loss = " << _one_iteration(inData, labData, dataLen, lr) << endl;
		print();
	}
	for (int i = 0; i < dataLen; i++) {
		delete[]inData[i];
		delete[]labData[i];
	}
	delete[]inData;
	delete[]labData;
	//delete[]dataVec;
	//delete[]lables;
}
double Perceptron::_one_iteration(double** indata, double** lables, int dataLen, double lr) {
	double LOSS = 0.0l;
	for (int i = 0; i < dataLen; i++) {
		vector<double> tempin;
		vector<double> templab;
		//double templab;
		tempin.resize(num_input);
		templab.resize(num_output);
		for (int j = 0; j < num_input; j++) {
			tempin[j] = indata[i][j];
		}
		for (int j = 0; j < num_output; j++) {
			templab[j] = lables[i][j];
		}
		//templab = indata[i][0];
		vector<double> res = predict(tempin);
		LOSS += update_weight(tempin, res, templab, lr);
	}
	return LOSS/dataLen;
}
double Perceptron::update_weight(vector<double> in, vector<double> out, vector<double> lable, double lr) {
	double loss = 0;
	/*print();
	cout << "data: ";
	for (auto i : in)cout << i << ' ';
	cout << ' ';
	for (auto i : lable)cout << i << ' ';
	cout << ' ';
	for (auto i : out)cout << i << ' ';
	cout << endl;*/
	for (int i = 0; i < num_output; i++) {
		double delt = lable[i] - out[i];
		for (int j = 0; j < num_input; j++) {
			weights[i][j] = weights[i][j] + delt * lr*in[j];
		}
		bias[i] += delt * lr;
		loss += delt;
	}
	//print();
	cout << endl;
	return loss;
	
}