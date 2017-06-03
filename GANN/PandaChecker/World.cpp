#include "World.h"

public void World::initWorld() {
	num_creatures = 20;
	for (int i = 0; i < num_creatures; i++) {
		creatures.add(new Creature());
	}
}
public void World::runNextGeneration() {

	selectBest();
	crossover();
	generation++;
}
public void World::update() {
	int curr_update = 0;
	while (curr_update < max_num_updates) {
		curr_update++;
	}
}
//For update
private void World::display();
private void World::updateCreature() {
	for (int i = 0; i < num_creatures; i++) {
		creatures[i].update();
		creatures[i].display();
	}
}
private void World::updateFitness() {
	total_fitness = 0;
	best_fitness = 0;
	avg_fitness = 0;
	for (int i = 0; i < num_creatures; i++) {
		total_fitness += creatures[i].fitness;
		if (best_fitness < creatures[i].fitness) { best_fitness = creatures[i].fitness; }
	}
	avg_fitness = total_fitness / num_creatures;
}
private void World::selectBest() {
	float r = Random();
	for (int i = 0; i < num_creatures; i++) {
		if (creatures[i].fitness / total_fitness) {
			if (r <= creatures[i].fitness / total_fitness) {
				parents.add(creatures[i]);
			}
		}
	}
}
private void World::crossover() {

}
