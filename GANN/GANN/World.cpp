#include <iostream>
#include "World.h"

using namespace std;

World::World() {

}

World * World::instance = 0;
void World::setInstance(World * w) {
	instance = w;
}

//==OPENGL FUNCTION==//
void World::displayWrapper() {
	instance->display();
}

void World::updateWrapper() {
	if (!instance->is_done) {
		instance->update();
	}
}

//Must be called after initWorld()
void World::initDisplay(int argc, char** argv) {
	//Display
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(480, 0);
	glutInitWindowSize(screen_width, screen_height);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(displayWrapper);
	glutReshapeFunc(reshape);
	glutIdleFunc(updateWrapper);
	// enter GLUT event processing cycle
	glutMainLoop();

}

void World::reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1, 1);

	// Update OpenGL viewport and internal variables
	glViewport(0, 0, w, h);
}
//===================//

void World::initWorld() {
	is_done = false;
	curr_update = 0;
	num_obstacles = 10;
	num_creatures = 28;
	generation = 0;
	mutation_rate = 0.001;
	selection_perc = 0.4;
	max_num_updates = 600;
	max_num_generation = 40;

	obstacles = new(Obstacle[num_obstacles]);
	creatures = new(Creature[num_creatures]);
	new_creatures = new(Creature[num_creatures]);

	cout << "beginning init" << endl;
	//init obstacles
	for (int i = 0; i < num_obstacles; i++) {
		obstacles[i] = Obstacle();
		obstacles[i].x_bounds = screen_width;
		obstacles[i].y_bounds = screen_height;
	}
	//init creatures
	for (int i = 0; i < num_creatures; i++) {
		//creatures[i] = Creature(num_obstacles *4 /*4 properties*/ + 4,  2 /*binary decision of left or right*/);
		creatures[i] = Creature(num_obstacles * 4 /*4 properties*/ + 4, 4 /*all direction*/);
		creatures[i].x_bounds = screen_width;
		creatures[i].y_bounds = screen_height;
	}
	resetPositions();
}

void World::resetPositions() {
	for (int i = 0; i < num_obstacles; i++) {
		obstacles[i].x_velocity = -4 * ((rand() % 101) / 100.0) + 2;
		obstacles[i].y_velocity = -4 * ((rand() % 101) / 100.0) + 2; //start by moving downard
		//set its position randomly on screen
		obstacles[i].x_pos = (rand() % (screen_width / 3)) + (screen_width / 3);
		obstacles[i].y_pos = (rand() % (2 * (screen_height / 3))) + (screen_height / 3);
	}
	for (int i = 0; i < num_creatures; i++) {
		//set its position randomly on screen
		creatures[i].x_pos = (rand() % (screen_width / 3)) + (screen_width / 3);
		creatures[i].y_pos = (rand() % (screen_height + 1));
	}
}

void World::run() {
	is_done = false;
	update();
}

void World::runNextGeneration() {
	curr_update = 0;
	num_new_creatures = 0;
	generation++;
	if (generation > max_num_generation) {
		is_done = true;
		cout << "finished" << endl;
	} else {
		//crossover until we have enough creatures
		while (num_new_creatures < num_creatures) {
			crossover();
		}

		//Make new obstacles
		for (int i = 0; i < num_obstacles; i++) {
			obstacles[i] = Obstacle();
			obstacles[i].x_bounds = screen_width;
			obstacles[i].y_bounds = screen_height;
		}

		for (int i = 0; i < num_creatures; i++) {
			creatures[i].nn->~NeuralNetwork();
			creatures[i] = new_creatures[i];
			creatures[i].fitness = 0;
			creatures[i].x_bounds = screen_width;
			creatures[i].y_bounds = screen_height;
		}
		resetPositions();
		cout << "GENERATION " << generation << " STARTED!" << endl;
	}
}

void World::update() {
	updateCreatures();
	updateObstacles();
	checkCollision();
	//display();
	glutPostRedisplay();

	curr_update++;
	Sleep(50);
	//cout << curr_update << " tick(s) passed" << endl;

	if (curr_update > max_num_updates) {
		updateFitness();
		selectBest();
		runNextGeneration();
	}
}

void World::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < num_creatures; i++) {
		creatures[i].display();
	}
	for (int i = 0; i < num_obstacles; i++) {
		obstacles[i].display();
	}
	glutSwapBuffers();
}

void World::updateCreatures() {
	for (int i = 0; i < num_creatures; i++) {
		//send input: [x1, y1, vx1, vy1, x2, y2, vx2, vy2, x3, y3, vx3, vy3, creature_x, creature_y, creature_vx, creature_vy] 16
		int * x = new (int[(num_obstacles*4) + 4]);
		for (int j = 0; j < num_obstacles; j++) {
			for (int k = 0; k < 4; k++) {
				if (k == 0) {
					//x[(j * 4) + k] = (obstacles[j].x_pos - creatures[i].x_pos) / abs(obstacles[j].x_pos - creatures[i].x_pos);
					x[(j * 4) + k] = (obstacles[j].x_pos - creatures[i].x_pos);
				}
				if (k == 1) {
					//x[(j * 4) + k] = (obstacles[j].y_pos - creatures[i].y_pos) / abs(obstacles[j].y_pos - creatures[i].y_pos);
					x[(j * 4) + k] = (obstacles[j].y_pos - creatures[i].y_pos);
				}
				if (k == 2) {
					x[(j * 4) + k] = obstacles[j].x_velocity - creatures[i].x_velocity;
				}
				if (k == 3) {
					x[(j * 4) + k] = obstacles[j].y_velocity - creatures[i].y_velocity;
				}
			}
		}
		for (int j = num_obstacles * 4; j < num_obstacles * 4 + 4; j++) {
			int k = j - num_obstacles * 4;
			if (k == 0) {
				x[j] = creatures[i].x_pos;
			}
			if (k == 1) {
				x[j] = creatures[i].y_pos;
			}
			if (k == 2) {
				x[j] = creatures[i].x_velocity;
			}
			if (k == 3) {
				x[j] = creatures[i].y_velocity;
			}
		}
		creatures[i].nn->sendInput(x);
		creatures[i].nn->train();
		creatures[i].update();
		creatures[i].fitness-=2;
		if (creatures[i].fitness < 1) {
			creatures[i].fitness = 1;
		}
	}
	//cout << creatures[1].nn->getOutput()[0] << "," << creatures[1].nn->getOutput()[1] << endl;
}

void World::updateObstacles() {
	for (int i = 0; i < num_obstacles; i++) {
		obstacles[i].update();
	}
}

float distance(Obstacle o, Creature c) {
	return sqrt(pow(o.x_pos - c.x_pos, 2) + pow(o.y_pos - c.y_pos, 2));
}
void World::checkCollision() {
	for (int i = 0; i < num_obstacles; i++) {
		for (int j = 0; j < num_creatures; j++) {
			if (distance(obstacles[i], creatures[j]) < 20) {
				creatures[j].fitness += 15;//20*(1/distance(obstacles[i], creatures[j]));
				if (creatures[j].fitness < 0) {
					creatures[j].fitness = 0;
				}
			}
		}
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
			creatures[i].fitness = creatures[i].fitness*0.8; //reduce fitness, so it might not be chosen again.
			return creatures[i];
		} else {
			current_prob += selection_probability;
		}
	}
	return creatures[0];
}

void World::crossover() {
	Creature parent1 = selectParent();
	updateFitness();
	Creature parent2 = selectParent();
	updateFitness();

	float num_inputs = num_obstacles * 4 /*4 properties*/ + 4;

	//Creature child1 = Creature(num_inputs, 2 /*binary decision of left or right*/);
	//Creature child2 = Creature(num_inputs, 2 /*binary decision of left or right*/);
	Creature child1 = Creature(num_inputs, 4 /*all direction*/);
	Creature child2 = Creature(num_inputs, 4 /*all direction*/);
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
				if (r <= mutation_rate) {
					float rH = (1 / sqrt((double)curr_n_inputs));
					child1_weigths[0][i][j][k] = (((double)(rand() % 100) + 1) / 100 * 2 * rH) - rH;
					child2_weigths[0][i][j][k] = (((double)(rand() % 100) + 1) / 100 * 2 * rH) - rH;
					cout << "mutation occured" << endl;
				}else if (r <= 0.5) {
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
