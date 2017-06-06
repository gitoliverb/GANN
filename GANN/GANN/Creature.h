#pragma once
#include <list>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <ctime>
#include "NeuralNetwork.h"

class Creature {
public:
	double fitness;
	NeuralNetwork nn;
	double x_pos;
	double y_pos;
	double x_velocity;
	double y_velocity;
	double max_velocity;

public:
	Creature();
	void update();
	void display();

};