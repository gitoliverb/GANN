#include "Creature.h"


NeuralNetwork setUpNN() {
	int num_inputs = 30;
	int num_layers = 3;
	int num_outputs = 2;
	int* hidden_layers = new(int[num_layers]);
	hidden_layers[0] = 3;
	hidden_layers[1] = 5;
	hidden_layers[2] = 3;

	NeuralNetwork nn(num_inputs, num_layers, hidden_layers, num_outputs);
	return nn;
}

Creature::Creature() {
	nn = setUpNN();
	nn.initNeuralNetwork();
}
