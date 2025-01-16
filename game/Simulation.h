#pragma once

#include <vector>
#include "Entity.h"

class Simulation {
public:
	bool getIsPaused() const { return isPaused; }
	int getTimeScale() const { return timeScale; }
	int getStepsPerSecond() const { return stepsPerSecond; }
	
	void toggleIsPaused();
	void setTimeScale(int newTimeScale);
	void updateStepsPerSecond();

	void updateSim(std::vector<Entity>& entities);
	
private:
	static constexpr double gravConstant = 6.67430e-11; // Gravitational Constant
	bool isPaused = false;
	int timeScale = 1;
	int stepsPerSecond = 1000 * timeScale;
};

