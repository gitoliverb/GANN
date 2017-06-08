#include <iostream>
#include "World.h"

using namespace std;

World::World() {

}

void World::initWorld() {
	screen_width = 480;	
	screen_height = 360;
	num_obstacles = 3;
	num_creatures = 20;
	generation = 0;
	selection_perc = 0.4;
	max_num_updates = 6000;
	max_num_generation = 1;

	obstacles = new(Obstacle[num_obstacles]);
	creatures = new(Creature[num_creatures]);
	new_creatures = new(Creature[num_creatures]);

	cout << "beginning init" << endl;
	//init obstacles
	for (int i = 0; i < num_obstacles; i++) {
		obstacles[i] = Obstacle();
		obstacles[i].x_bounds = screen_width;
		obstacles[i].y_bounds = screen_height;
		obstacles[i].y_velocity = -1 * rand()%2; //start by moving downard
		//set its position randomly on screen
		obstacles[i].x_pos = (rand() % (screen_width / 3)) + (screen_width / 3);
		obstacles[i].y_pos = (rand() % (2 * (screen_height / 3))) + (screen_height / 3);
	}
	//init creatures
	for (int i = 0; i < num_creatures; i++) {
		creatures[i] = Creature(num_obstacles*4 /*4 properties*/,  2 /*binary decision of left or right*/);
		//set its position randomly on screen
		creatures[i].x_pos = (rand() % (screen_width / 3)) + (screen_width / 3); 
		creatures[i].y_pos = (rand() % (screen_height / 3));
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
		creatures[i].nn->~NeuralNetwork();
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
	}
	//setup creatures and NNs for next run.
	updateFitness();
	selectBest();
	runNextGeneration();
	if (generation < max_num_generation) {
		update();
	}
	else {
		cout << "finished" << endl;
	}
}

void World::display() {
	for (int i = 0; i < num_creatures; i++) {
		creatures[i].display();
	}
}

void World::updateCreatures() {
	for (int i = 0; i < num_creatures; i++) {
		//send input: [x1, y1, vx1, vy1, x2, y2, vx2, vy2, x3, y3, vx3, vy3, creature_x, creature_y, creature_vx, creature_vy] 16
		int x[16] = {obstacles[0].x_pos, obstacles[0].y_pos, obstacles[0].x_velocity, obstacles[0].y_velocity,
					obstacles[1].x_pos, obstacles[1].y_pos, obstacles[1].x_velocity, obstacles[1].y_velocity,
					obstacles[2].x_pos, obstacles[2].y_pos, obstacles[2].x_velocity, obstacles[2].y_velocity,
					creatures[i].x_pos, creatures[i].y_pos, creatures[i].x_velocity, creatures[i].y_velocity};
		creatures[i].nn->sendInput(x);
		creatures[i].nn->train();
		creatures[i].update();
		creatures[i].fitness++;
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
	float r = (rand()%101) / 100.0;
	float current_prob = 0;

	for (int i = 0; i < num_creatures; i++) {
		float selection_probability = creatures[i].fitness / total_fitness;
		if (r >= current_prob && r <= current_prob + selection_probability) {
			//Found parent
			creatures[i].fitness = 0; //set fitness to 0, so it cannot be chosen again.
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
	double **** child1_weigths = child1.nn->getWeights();
	double **** child2_weigths = child2.nn->getWeights();

	int curr_n_inputs = child1.nn->n_inputs;
	//Each layer
	for (int i = 0; i < child1.nn->n_hidden_layers; i++) {
		double * curr_out = new(double[child1.nn->n_hidden_nodes[i]]);
		//Each node
		for (int j = 0; j < child1.nn->n_hidden_nodes[i]; j++) {
			//Each weight
			for (int k = 0; k < curr_n_inputs; k++) {
				float r = (rand() % 101) / 100.0;
				if (r <= 0.5) {
					child1_weigths[0][i][j][k] = parent1.nn->getWeights()[0][i][j][k];
					child2_weigths[0][i][j][k] = parent2.nn->getWeights()[0][i][j][k];
				}else {
					child1_weigths[0][i][j][k] = parent2.nn->getWeights()[0][i][j][k];
					child2_weigths[0][i][j][k] = parent1.nn->getWeights()[0][i][j][k];
				}
			}
		}
		curr_n_inputs = child1.nn->n_hidden_nodes[i];
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
	
	/*Print check to see if new child was made:
	cout << "||==CREATED TWO NEW CHILDREN==||" << endl;
	parent1.nn->printNetworkData();
	parent2.nn->printNetworkData();
	child1.nn->printNetworkData();
	child2.nn->printNetworkData();*/

}
