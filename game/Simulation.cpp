#include <iostream>
#include <vector>
#include <cmath>
#include "Simulation.h"
#include "../util/Vector2.h"
#include "raymath.h"

void Simulation::updateSim(std::vector<Entity>& entities) {
	// TODO: Make this work with more than 2 entities
	int mostMassIdx = findMostMassive(entities);

	// For now, we only calculate gravity between 2 entities
	Entity massiveBody = entities[mostMassIdx];
	long mass1 = massiveBody.getMass();
	util::Vector2 vel1 = massiveBody.getVelocity();
	util::Vector2 pos1 = massiveBody.getPosition();

	for (int i = 0; i < entities.size(); i++) {
		if (i == mostMassIdx) {
			continue;
		}

		Entity& entity = entities[i];
		long mass2 = entity.getMass();
		util::Vector2 vel2 = entity.getVelocity();
		util::Vector2 pos2 = entity.getPosition();

		// Get the difference in the X and Y positions of the two entities
		double dX = pos1.x - pos2.x;
		double dY = pos1.y - pos2.y;

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
		//Vector2 newVel1 = { accelX1 + vel1.x, accelY1 + vel1.y };
		//Vector2 newVel2 = { accelX2 + vel2.x, accelY2 + vel2.y };
		massiveBody.setVelocity(util::Vector2(accelX1 + vel1.x, accelY1 + vel1.y));
		entity.setVelocity(util::Vector2(accelX2 + vel2.x, accelY2 + vel2.y));

		// Update positions of each entity
		util::Vector2 newPos1(pos1.x + massiveBody.getVelocity().x, pos1.y + massiveBody.getVelocity().y);
		util::Vector2 newPos2(pos2.x + entity.getVelocity().x, pos2.y + entity.getVelocity().y);
		massiveBody.setPosition(newPos1);
		entity.setPosition(newPos2);
	}


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

// Finds entity with the largest mass
// Returns index of the most massive entity
int Simulation::findMostMassive(std::vector<Entity>& entities) {
	int mostMassIdx = 0;
	long largestMass = entities[0].getMass();
	for (int i = 0; i < entities.size(); i++) {
		long mass = entities[i].getMass();
		if (mass > largestMass) {
			largestMass = mass;
			mostMassIdx = i;
		}
	}
	return mostMassIdx;
}