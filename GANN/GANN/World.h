#pragma once
#include <list>
#include "Creature.h"

using namespace std;
class World {
public:
	Creature * creatures;
	Creature * new_creatures;
	int generation;
	int num_creatures;
	int max_num_updates;
	int max_num_generation;
	int num_new_creatures;
	float selection_perc;
	float mutation_rate;
	float crossover_rate;
	float total_fitness;
	float best_fitness;
	float avg_fitness;
public:
	World();
	void initWorld();
	void runNextGeneration();
	void run();
private:
	//For update
	void update();
	void display();
	void updateCreatures();
	void updateFitness();

	Creature selectParent();
	void selectBest();
	void crossover();

};