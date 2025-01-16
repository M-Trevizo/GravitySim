#pragma once

#include "raylib.h"
#include <vector>

class Entity {
public:
	Entity();
	Entity(long r, long m, Vector2 v, Vector2 pos);

	Vector2 getVelocity() const { return velocity; }
	Vector2 getPosition() const { return position; }
	int getMass() const { return mass; }

	void setVelocity(Vector2 updatedVelocity);
	void setPosition(Vector2 updatedPosition);
	

	static void drawEntity(Entity entity);
	static void drawEntities(const std::vector<Entity>& entities);

private:
	int radius;
	int mass;
	Vector2 velocity;
	Vector2 position;
};

