#pragma once
#include <list>
#include "Creature.h"

using namespace std;
class World {
public:
	Creature * creatures;
	Creature * parents;
	int generation;
	int num_creatures;
	int max_num_updates;
	float mutation_rate;
	float crossover_rate;
	float total_fitness;
	float best_fitness;
	float avg_fitness;

	void initWorld();
	void runNextGeneration();
	void update();
private:
	//For update
	void display();
	void updateCreature();

	void updateFitness();
	void selectBest();
	void crossover();

};