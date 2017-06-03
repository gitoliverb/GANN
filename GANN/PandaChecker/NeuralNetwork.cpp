#include "NeuralNetwork.h"
#include <iostream>
#include <fstream>


using namespace std;

NeuralNetwork::NeuralNetwork(int num_i, int num_hl, int* num_hn, int num_o) {
	n_inputs = num_i;
	n_outputs = num_o;
	n_hidden_layers = num_hl;
	n_hidden_nodes = new(int[n_hidden_layers]);
	for (int i = 0; i < n_hidden_layers; i++) {
		n_hidden_nodes[i] = num_hn[i];
	}
}


NeuralNetwork::~NeuralNetwork() {

}

//Setup weight for network
void NeuralNetwork::initNeuralNetwork() {

	cout << endl << "|==INITIALIZING NETWORK==|" << endl;

	int num_inputs = n_inputs;
	double rH = 1 / sqrt((double)num_inputs);

	//Number of hidden layers and output layer.
	weights = new(double**[n_hidden_layers + 1]);
	bias = new(double*[n_hidden_layers + 1]);
 
	srand(time(NULL));
	//Each layer
	for (int i = 0; i < n_hidden_layers; i++) {
		weights[i] = new(double*[n_hidden_nodes[i]]);
		bias[i] = new(double[n_hidden_nodes[i]]);

		cout << "layer " << i + 1 << " with " << n_hidden_nodes[i] << " nodes:" << endl;
		//Each node
		for (int j = 0; j < n_hidden_nodes[i]; j++) {
			weights[i][j] = new(double[num_inputs]);

			cout << "node " << j + 1 << " weights: " << endl;
			//Each input
			for (int k = 0; k < num_inputs; k++) {
				weights[i][j][k] = (((double)(rand() % 100) + 1) / 100 * 2 * rH) - rH;
			}
			for (int k = 0; k < num_inputs; k++) {
				cout << weights[i][j][k] << ", ";
			}
			cout << endl;

			bias[i][j] = (((double)(rand() % 100) + 1) / 100 * 2 * rH) - rH;
		}
		num_inputs = n_hidden_nodes[i];
		rH = 1 / sqrt((double)num_inputs);
	}

	//Add one for output layer
	rH = 1 / sqrt((double)num_inputs);
	weights[n_hidden_layers] = new(double*[n_outputs]);
	//Each output node
	for (int j = 0; j < n_outputs; j++) {
		weights[n_hidden_layers][j] = new(double[num_inputs]);

		cout << "output node " << j + 1 << " weights: " << endl;
		//Each input
		for (int k = 0; k < num_inputs; k++) {
			weights[n_hidden_layers][j][k] = (((double)(rand() % 100) + 1) / 100 * 2 * rH) - rH;
		}
		for (int k = 0; k < num_inputs; k++) {
			cout << weights[n_hidden_layers][j][k] << ", ";
		}
		cout << endl;
	}
}

double NeuralNetwork::sigmoid(double z) {
	return 1 / (1 + exp(-z));
}

double NeuralNetwork::dot(double* w, double* x) {
	return 0;
}

void NeuralNetwork::sendInput(string x) {
	inputs = new(double[n_inputs]);
	for (int i = 0; i < n_inputs; i++) {
		//inputs[i] = (double)stoi(&(x.at[i]), nullptr, 2);
		if (x.size() > i) {
			inputs[i] = (int)x.at(i);
		}
		else {
			inputs[i] = 0;
		}
	}
	cout << endl << "|==PRINTING INPUT==|" << endl;
	for (int i = 0; i < n_inputs; i++) {
		cout << "input node: " << i + 1 << endl;
		cout << "value: " << inputs[i] << endl;
	}
	//cout << "Finished" << endl;
}

double * NeuralNetwork::getLayerOutput(int curr_hidden_layer, int curr_num_nodes, double * x, int curr_num_inputs) {
	return 0;
}

void NeuralNetwork::trainHelper(double * x) {
	double * curr_input = x;
	double * curr_output;
	int curr_n_inputs = n_inputs;
	//Each layer
	for (int i = 0; i < n_hidden_layers; i++) {
		double * curr_out = new(double[n_hidden_nodes[i]]);
		//Each node
		for (int j = 0; j < n_hidden_nodes[i]; j++) {
			double z = 0;
			//Each weight
			for (int k = 0; k < curr_n_inputs; k++) {
				z += weights[i][j][k] * curr_input[k];
			}
			z += bias[i][j];
			curr_out[j] = NeuralNetwork::sigmoid(z);
		}
		curr_n_inputs = n_hidden_nodes[i];
		curr_input = curr_out;
	}
	outputs = curr_input;
}
void NeuralNetwork::train(int max_num_train) {
	for (int i = 0; i < max_num_train; i++) {
		trainHelper(inputs);
	}
}
void NeuralNetwork::printNetworkData() {
	cout << endl << "|==PRINTING NODE AND LAYERS OF NETWORK==|" << endl;
	for (int i = 0; i < n_hidden_layers; i++) {
		cout << "layer: " << i + 1 << endl;
		cout << "nodes: " << n_hidden_nodes[i] << endl;
	}
}

void NeuralNetwork::printOutputs() {
	cout << endl << "|==PRINTING OUTPUT==|" << endl;
	for (int i = 0; i < n_outputs; i++) {
		cout << "output node: " << i + 1 << endl;
		cout << "value: " << outputs[i] << endl;
	}
}

#include "stdafx.h"
