#include <random>
#include "Entity.h"
#include "Game.h"

Entity::Entity() {
	radius = 1;
	mass = 1;
	velocity = util::Vector2(0, 0);

	double x = rand() % 800;
	double y = rand() % 600;
	position = util::Vector2(x, y);
}

Entity::Entity(long r, long m, util::Vector2 v, util::Vector2 pos) {
	radius = r;
	mass = m;
	velocity = v;
	position = pos;
}

void Entity::setVelocity(util::Vector2 updatedVelocity) {
	velocity = updatedVelocity;
}

void Entity::setPosition(util::Vector2 updatedPosition) {
	position = updatedPosition;
}

void Entity::drawEntity(Entity entity) {
	int radius = entity.radius;
	int posX = entity.position.x;
	int posY = entity.position.y;

	DrawCircle(posX, posY, radius, WHITE);
}

void Entity::drawEntities(const std::vector<Entity>& entities) {
	for (int i = 0; i < entities.size(); i++) {
		int radius = entities[i].radius;
		int posX = entities[i].position.x;
		int posY = entities[i].position.y;

		DrawCircle(posX, posY, radius, WHITE);
	}
}