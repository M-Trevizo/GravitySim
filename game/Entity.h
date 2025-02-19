#pragma once

#include "raylib.h"
#include "../util/Vector2.h"

#include <vector>
#include <deque>

class Entity {
public:
	Entity();
	Entity(double r, double m, util::Vector2 v, util::Vector2 pos);
	Entity(double r, double m, util::Vector2 v, util::Vector2 pos, Color c);

	util::Vector2 getVelocity() const { return velocity; }
	util::Vector2 getPosition() const { return position; }
	double getMass() const { return mass; }

	void setVelocity(util::Vector2 updatedVelocity);
	void setPosition(util::Vector2 updatedPosition);

	static void drawEntity(Entity entity);
	static void drawEntities(std::vector<Entity>& entities);
	
	/*
	void drawTrail() const;
	void pushToTrailBuffer(Vector2 pos);
	*/

private:
	static constexpr double distanceScale = 1e-5;			// Scale Distance

	double radius;
	double mass;
	util::Vector2 velocity;
	util::Vector2 position;

	Color color;
	std::deque<Vector2> trailBuffer;						// Hold position info for drawing a trail

};

