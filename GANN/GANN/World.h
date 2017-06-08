#pragma once
#include <list>
#include "Creature.h"
#include "Obstacle.h"

using namespace std;
class World {
public:
	Obstacle * obstacles;
	Creature * creatures;
	Creature * new_creatures;
	int generation;
	int num_obstacles;
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

	//display settings
	int screen_width;
	int screen_height;
public:
	World();
	void initWorld();
	void runNextGeneration();
	void run();
private:
	void initObstacles();

	//For update
	void update();
	void display();
	void updateCreatures();
	void updateFitness();

	Creature selectParent();
	void selectBest();
	void crossover();

};