#pragma once

#include "raylib.h"
#include "../util/Vector2.h"

#include <vector>

class Entity {
public:
	Entity();
	Entity(long r, double m, util::Vector2 v, util::Vector2 pos);

	util::Vector2 getVelocity() const { return velocity; }
	util::Vector2 getPosition() const { return position; }
	double getMass() const { return mass; }

	void setVelocity(util::Vector2 updatedVelocity);
	void setPosition(util::Vector2 updatedPosition);
	

	static void drawEntity(Entity entity);
	static void drawEntities(const std::vector<Entity>& entities);

private:
	long radius;
	double mass;
	util::Vector2 velocity;
	util::Vector2 position;
};

