#include "Creature.h"
#include "NeuralNetwork.h"

NeuralNetwork * setUpCreatureNN() {
	int num_inputs = 30;
	int num_layers = 3;
	int num_outputs = 2;
	int* hidden_layers = new(int[num_layers]);
	hidden_layers[0] = 3;
	hidden_layers[1] = 5;
	hidden_layers[2] = 3;

	return new NeuralNetwork(num_inputs, num_layers, hidden_layers, num_outputs);
}

NeuralNetwork * setUpCreatureNN(int num_inputs, int num_outputs) {
	int num_layers = 3;
	int* hidden_layers = new(int[num_layers]);
	hidden_layers[0] = 3;
	hidden_layers[1] = 5;
	hidden_layers[2] = 3;

	return new NeuralNetwork(num_inputs, num_layers, hidden_layers, num_outputs);
}

Creature::Creature() {
	x_pos = 0;
	y_pos = 0;
	x_velocity = 0;
	y_velocity = 0;
	fitness = 0;

	nn = setUpCreatureNN();
	nn->initNeuralNetwork();
}

Creature::Creature(int num_inputs, int num_outputs) {
	x_pos = 0;
	y_pos = 0;
	x_velocity = 0;
	y_velocity = 0;
	fitness = 0;

	nn = setUpCreatureNN(num_inputs, num_outputs);
	nn->initNeuralNetwork();
}

void Creature::update() {
	x_velocity = nn->getOutput()[0];
	y_velocity = nn->getOutput()[1];
	x_pos += x_velocity;
	y_pos += y_velocity;
	
	//Check bounds
	if (x_pos >= x_bounds) {
		x_pos = x_bounds;
	}
	if (x_pos <= x_bounds) {
		x_pos = 0;
	}
	if (y_pos >= y_bounds) {
		y_pos = y_bounds;
	}
	if (y_pos <= y_bounds) {
		y_pos = 0;
	}
	
}

void Creature::display() {

}
