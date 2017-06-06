#include <iostream>
#include "World.h"

using namespace std;

World::World() {

}

void World::initWorld() {
	num_creatures = 8;
	generation = 0;
	selection_perc = 0.4;
	max_num_updates = 60;
	max_num_generation = 1;

	creatures = new(Creature[num_creatures]);
	new_creatures = new(Creature[num_creatures]);
	cout << "beginning init" << endl;
	for (int i = 0; i < num_creatures; i++) {
		creatures[i] = Creature();
	}
}

void World::run() {
	update();
}

void World::runNextGeneration() {
	num_new_creatures = 0;
	//crossover until we have enough creatures
	while (num_new_creatures < num_creatures) {
		crossover();
	}

	for (int i = 0; i < num_creatures; i++) {
		creatures[i] = new_creatures[i];
	}
	generation++;
}

void World::update() {
	int curr_update = 0;
	//update loop
	while (curr_update < max_num_updates) {
		updateCreatures();
		display();
		curr_update++;
		cout << curr_update;
	}
	//setup creatures and NNs for next run.
	updateFitness();
	selectBest();
	runNextGeneration();
	if (generation < max_num_generation) {
		update();
	}
}

void World::display() {
	for (int i = 0; i < num_creatures; i++) {
		creatures[i].display();
	}
}

void World::updateCreatures() {
	for (int i = 0; i < num_creatures; i++) {
		creatures[i].update();
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
	for(int i = 0; i < num_creatures; i++){
		if(creatures[i].fitness/ total_fitness >= total_fitness*selection_perc)
		if (i > (int)(num_creatures*selection_perc + 0.5)) {
			break;
		}
	}
}

Creature World::selectParent() {
	float r = rand() % 1;
	float current_prob = 0;

	for (int i = 0; i < num_creatures; i++) {
		float selection_probability = creatures[i].fitness / total_fitness;
		if (r >= current_prob && r <= current_prob + selection_probability) {
			//Found parent
			creatures[i].fitness = 0;
			return creatures[i];
		} else {
			current_prob += selection_probability;
		}
	}
}

void World::crossover() {
	Creature parent1 = selectParent();
	updateFitness();
	Creature parent2 = selectParent();
	updateFitness();

	Creature child1 = Creature();
	Creature child2 = Creature();
	double **** child1_weigths = child1.nn.getWeights();
	double **** child2_weigths = child2.nn.getWeights();

	int curr_n_inputs = child1.nn.n_inputs;
	//Each layer
	for (int i = 0; i < child1.nn.n_hidden_layers; i++) {
		double * curr_out = new(double[child1.nn.n_hidden_nodes[i]]);
		//Each node
		for (int j = 0; j < child1.nn.n_hidden_nodes[i]; j++) {
			//Each weight
			for (int k = 0; k < curr_n_inputs; k++) {
				float r = rand() % 1;
				if (r <= 0.5) {
					*child1_weigths[i][j][k] = *parent1.nn.getWeights()[i][j][k];
					*child2_weigths[i][j][k] = *parent2.nn.getWeights()[i][j][k];
				}
				else {
					*child1_weigths[i][j][k] = *parent2.nn.getWeights()[i][j][k];
					*child2_weigths[i][j][k] = *parent1.nn.getWeights()[i][j][k];
				}
			}
		}
		curr_n_inputs = child1.nn.n_hidden_nodes[i];
	}

	//Add creatures to next generation creatures.
	new_creatures[num_new_creatures] = parent1;
	num_new_creatures++;
	new_creatures[num_new_creatures] = parent2;
	num_new_creatures++;
	new_creatures[num_new_creatures] = child1;
	num_new_creatures++;
	new_creatures[num_new_creatures] = child2;
	num_new_creatures++;

	cout << "||==CREATED TWO NEW CHILDREN==||" << endl;
	parent1.nn.printNetworkData();
	parent2.nn.printNetworkData();
	child1.nn.printNetworkData();
	child2.nn.printNetworkData();

}
