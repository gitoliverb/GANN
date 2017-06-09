#include "Obstacle.h"

Obstacle::Obstacle(){
	x_pos = 0;
	y_pos = 0;
	x_velocity = 0;
	y_velocity = 0;
}

void Obstacle::update()
{
	x_pos += x_velocity;
	y_pos += y_velocity;

	//Check bounds and bounce if out of bounds
	if (x_pos >= x_bounds) {
		x_pos = x_bounds;
		x_velocity = -x_velocity;
	}
	if (x_pos <= 0) {
		x_pos = 0;
		x_velocity = -x_velocity;
	}
	if (y_pos >= y_bounds) {
		y_pos = y_bounds;
		y_velocity = -y_velocity;
	}
	if (y_pos <= 0) {
		y_pos = 0;
		y_velocity = -y_velocity;
	}
}

void Obstacle::display()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	/*
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	*/

	glBegin(GL_POLYGON);
		glVertex3f(x_pos, y_pos, 0.0);
		glVertex3f(x_pos + 10, y_pos, 0.0);
		glVertex3f(x_pos + 10, y_pos + 10, 0.0);
		glVertex3f(x_pos, y_pos + 10, 0.0);
	glEnd();

	//glutSwapBuffers();
}
