#pragma once
#include <list>
#include <glut.h>
#include <windows.h>
#include "Creature.h"
#include "Obstacle.h"

using namespace std;
class World {
protected:
	static World * instance;
public:
	Obstacle * obstacles;
	Creature * creatures;
	Creature * new_creatures;

	int generation;
	int curr_update;
	int num_obstacles;
	int num_creatures;
	int num_new_creatures;
	int num_input_properties;
	int num_output_properties;
	int max_num_updates;
	int max_num_generation;

	float selection_perc;
	float mutation_rate;
	float crossover_rate;
	float total_fitness;
	float best_fitness;
	float avg_fitness;

	bool is_done;

	//display settings
	static const int screen_width=480;
	static const int screen_height=360;
public:
	World();
	void initWorld();
	void runNextGeneration();
	void run();

	//opengl
	static void setInstance(World * w);
	void initDisplay(int argc, char** argv);
	static void displayWrapper();
	static void updateWrapper();
	static void reshape(int w, int h);
private:
	void resetPositions();

	//For update
	void update();
	void checkCollision();
	virtual void display();
	void inputStyle1();
	void inputStyle2();
	void updateCreatures();
	void updateObstacles();
	void updateFitness();

	Creature selectParent();
	void selectBest();
	void crossover();

};