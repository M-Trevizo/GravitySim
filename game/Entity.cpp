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

Entity::Entity(long r, double m, util::Vector2 v, util::Vector2 pos) {
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
	float radius = static_cast<float>(entity.radius);
	int posX = static_cast<int>(entity.position.x);
	int posY = static_cast<int>(entity.position.y);

	DrawCircle(posX, posY, radius, WHITE);
}

void Entity::drawEntities(const std::vector<Entity>& entities) {
	for (int i = 0; i < entities.size(); i++) {
		float radius = static_cast<float>(entities[i].radius);
		int posX = static_cast<int>(entities[i].position.x);
		int posY = static_cast<int>(entities[i].position.y);

		DrawCircle(posX, posY, radius, WHITE);
	}
}