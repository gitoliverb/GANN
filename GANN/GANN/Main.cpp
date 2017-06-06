// Main.cpp : Defines the entry point for the console application.
//

#include "World.h"

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

void testNeuralNetwork() {
	NeuralNetwork nn = setUpNN();

	nn.initNeuralNetwork();
	string  s = "hello world";
	nn.sendInput(s);
	nn.printNetworkStructure();
	nn.printNetworkData();
	nn.train(1);
	nn.printOutputs();
}

void testWorld() {	//not working yet
	World w = World();
	w.initWorld();
	w.run();
}

int main(int argc, char** argv) {
	testNeuralNetwork();
	//testWorld();
	//return 0;
}
