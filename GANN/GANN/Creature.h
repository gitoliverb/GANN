#pragma once
#include <list>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <glut.h>
#include "NeuralNetwork.h"

class Creature {
public:
	double fitness;
	NeuralNetwork * nn;
	double x_pos;
	double y_pos;
	double x_velocity;
	double y_velocity;
	double max_velocity;
	double x_bounds;
	double y_bounds;

public:
	Creature();
	Creature(int num_inputs, int num_outputs);
	void update();
	void display();

};