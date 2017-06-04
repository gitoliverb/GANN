#include "World.h"



void World::initWorld() {
	num_creatures = 20;
	for (int i = 0; i < num_creatures; i++) {
		creatures[i] = Creature();
	}
}
void World::runNextGeneration() {

	selectBest();
	crossover();
	generation++;
}
void World::update() {
	int curr_update = 0;
	while (curr_update < max_num_updates) {
		curr_update++;
	}
}

//For update
void World::display() {

}

void World::updateCreature() {
	for (int i = 0; i < num_creatures; i++) {
		creatures[i].update();
		creatures[i].display();
	}
}

void World::updateFitness() {
	total_fitness = 0;
	best_fitness = 0;
	avg_fitness = 0;
	for (int i = 0; i < num_creatures; i++) {
		total_fitness += creatures[i].fitness;
		if (best_fitness < creatures[i].fitness) { best_fitness = creatures[i].fitness; }
	}
	avg_fitness = total_fitness / num_creatures;
}

void World::selectBest() {
	float r = rand();
	for (int i = 0; i < num_creatures; i++) {
		if (creatures[i].fitness / total_fitness) {
			if (r <= creatures[i].fitness / total_fitness) {
				parents[i] = creatures[i];
			}
		}
	}
}

void World::crossover() {

}
