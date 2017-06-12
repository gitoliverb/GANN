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
	int num_layers = 2;
	int* hidden_layers = new(int[num_layers]);
	hidden_layers[0] = 150;
	hidden_layers[1] = 16;
	//hidden_layers[2] = 16;
	//hidden_layers[3] = 10;
	//hidden_layers[4] = 5;
	//hidden_layers[5] = 10;
	//hidden_layers[6] = 20;
	//hidden_layers[7] = 40;
	//hidden_layers[8] = 80;

	return new NeuralNetwork(num_inputs, num_layers, hidden_layers, num_outputs);
}

Creature::Creature() {
	x_pos = 0;
	y_pos = 0;
	x_velocity = 0;
	y_velocity = 0;
	fitness = 500;

	nn = setUpCreatureNN();
	nn->initNeuralNetwork();
}

Creature::Creature(int num_inputs, int num_outputs) {
	x_pos = 0;
	y_pos = 0;
	x_velocity = 0;
	y_velocity = 0;
	fitness = 500;

	nn = setUpCreatureNN(num_inputs, num_outputs);
	nn->initNeuralNetwork();
}

void Creature::update() {
	x_velocity = 9 * (nn->getOutput()[0] - nn->getOutput()[1]);
	y_velocity = 9 * (nn->getOutput()[2] - nn->getOutput()[3]);
	x_pos += x_velocity;
	y_pos += y_velocity;
	
	//Check bounds
	if (x_pos >= x_bounds - 10) {
		x_pos = x_bounds - 10;
	}
	if (x_pos <= 0) {
		x_pos = 0;
	}
	if (y_pos >= y_bounds - 10) {
		y_pos = y_bounds-10;
	}
	if (y_pos <= 0) {
		y_pos = 0;
	}
	
}

void Creature::display() {
	
	glColor4f(0.0, -1*fmax(-1.0, -fitness/500), 0.5, 1.0);
	/*
	glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	*/
	glBegin(GL_POLYGON);
		glVertex3f(x_pos, y_pos, 0.0);
		glVertex3f(x_pos + 10, y_pos, 0.0);
		glVertex3f(x_pos + 10, y_pos + 10, 0.0);
		glVertex3f(x_pos, y_pos + 10, 0.0);
	glEnd();

	
}
