#pragma once

class Obstacle {
public:
	double x_pos;
	double y_pos;
	double x_velocity;
	double y_velocity;
	double max_velocity;
	double x_bounds;
	double y_bounds;

public:
	Obstacle();
	void update();
	void display();

};