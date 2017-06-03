#pragma once
#include <list>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <ctime>
#include "NeuralNetwork.h"

class Creature {
public:
	double fitness_level;
	NeuralNetwork nn;

public:
	Creature();
	void update();
	void display();

};