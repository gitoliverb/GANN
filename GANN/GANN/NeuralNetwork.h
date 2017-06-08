#pragma once
#include <list>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <ctime>

using namespace std;
class NeuralNetwork {
private:
	double* inputs;
	double* outputs;
	double*** weights;
	double** bias;
private:
	void trainHelper(double * x);

public:
	int n_inputs;
	int n_outputs;
	int n_hidden_layers;
	int* n_hidden_nodes;
public:
	//constructor
	NeuralNetwork();
	NeuralNetwork(int num_i, int num_hl, int* num_hn, int num_o);
	~NeuralNetwork();
	void initNeuralNetwork();
	double sigmoid(double z);
	double dot(double* w, double* x);
	void sendInput(string x);
	void sendInput(int* x);
	void train();
	void train(int max_num_train);
	void printNetworkStructure();
	void printNetworkData();
	void printOutputs();
	double**** getWeights();
	double * getOutput();
};