#include <random>
#include <iostream>
#include "Entity.h"
#include "Game.h"

Entity::Entity() {
	radius = 1;
	mass = 1;
	velocity = util::Vector2(0, 0);

	double x = rand() % 800;
	double y = rand() % 600;
	position = util::Vector2(x, y);

	color = WHITE;
}

Entity::Entity(double r, double m, util::Vector2 v, util::Vector2 pos) {
	radius = r;
	mass = m;
	velocity = v;
	position = pos;
	color = WHITE;
}

Entity::Entity(double r, double m, util::Vector2 v, util::Vector2 pos, Color c) {
	radius = r;
	mass = m;
	velocity = v;
	position = pos;
	color = c;
}

void Entity::setVelocity(util::Vector2 updatedVelocity) {
	velocity = updatedVelocity;
}

void Entity::setPosition(util::Vector2 updatedPosition) {
	position = updatedPosition;
}

void Entity::drawEntity(Entity entity) {
	float radius = static_cast<float>(entity.radius);
	int posX = static_cast<int>(entity.position.x) * distanceScale;
	int posY = static_cast<int>(entity.position.y) * distanceScale;
	Color color = entity.color;

	DrawCircle(posX, posY, radius, color);
}

void Entity::drawEntities(std::vector<Entity>& entities) {
	for (int i = 0; i < entities.size(); i++) {
		Entity& entity = entities[i];
		
		float radius = static_cast<float>(entity.radius);
		int posX = static_cast<int>(entity.position.x * distanceScale) + GetScreenWidth();
		int posY = static_cast<int>(entity.position.y * distanceScale) + GetScreenHeight();
		Color color = entity.color;

		DrawCircle(posX, posY, radius, color);
	}
}

/*
* For now, drawing trails is too slow to work
* Maybe I'll come back to it another time.
*/

/*
void Entity::pushToTrailBuffer(Vector2 pos) {
	if (trailBuffer.size() >= 1000) {
		trailBuffer.pop_front();
	}
	trailBuffer.push_back(pos);
}

void Entity::drawTrail() const {
	for (Vector2 pos : trailBuffer) {
		DrawPixelV(pos, WHITE);
	}
}
*/

