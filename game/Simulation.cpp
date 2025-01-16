#include <iostream>
#include <vector>
#include <cmath>
#include "Simulation.h"

void Simulation::updateSim(std::vector<Entity>& entities) {
	// For now, we only calculate gravity between 2 entities
	Entity body1 = entities[0];
	Entity body2 = entities[1];

	int mass1 = body1.getMass();
	int mass2 = body2.getMass();
	Vector2 vel1 = body1.getVelocity();
	Vector2 vel2 = body2.getVelocity();

	// Get the difference in the X and Y positions of the two entities
	Vector2 pos1 = body1.getPosition();
	Vector2 pos2 = body2.getPosition();
	int dX = pos1.x - pos2.x;
	int dY = pos1.y - pos2.y;

	// Calculate distance using pythagoras
	double distance = sqrt(pow(dX, 2) + pow(dY, 2));

	// Calculate gravitation force using Newtonian gravity
	double gravForce = gravConstant * ((mass1 * mass2) / pow(distance, 2));

	// Calculate acceleration for both bodies (should be in m/s^2)
	double acceleration1 = gravForce / mass1;
	double acceleration2 = gravForce / mass2;

	// Update velocities of each entity
	// Need to calculate theta for both the X and Y directions
	// These are in radians
	double thetaX = acos(dX / distance); 
	double thetaY = asin(dY / distance);
	
	
	// Find x and y components of the acceleration vector. 
	// e.g. for a vector with magnitude of 10m/s^2 and is 45deg off the x-axis
	// x component = 10 * cos(45)
	// y component = 10 * sin(45)
	double accelX1 = acceleration1 * cos(thetaX);
	double accelY1 = acceleration1 * sin(thetaY);
	double accelX2 = acceleration2 * cos(thetaX);
	double accelY2 = acceleration2 * sin(thetaY);
	Vector2 newVel1 = { accelX1 + vel1.x, accelY1 + vel1.y };
	Vector2 newVel2 = { accelX2 + vel2.x, accelY2 + vel2.y };
	entities[0].setVelocity(newVel1);
	entities[1].setVelocity(newVel2);

	// Update positions of each entity
	Vector2 newPos1 = { pos1.x + entities[0].getVelocity().x, pos1.y + entities[0].getVelocity().y };
	Vector2 newPos2 = { pos2.x + entities[1].getVelocity().x, pos2.y + entities[1].getVelocity().y };
	entities[0].setPosition(newPos1);
	entities[1].setPosition(newPos2);
}

void Simulation::toggleIsPaused() {
	isPaused = !isPaused;
}

void Simulation::setTimeScale(int newTimeScale) {
	timeScale = newTimeScale;
}

void Simulation::updateStepsPerSecond() {
	stepsPerSecond = timeScale * 1000;
}