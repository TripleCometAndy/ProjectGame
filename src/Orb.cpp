#include "Orb.h"
#include "Hitbox.h"
#include "Wall.h"

#include <iostream>
#include <algorithm>

Orb::Orb(double x, double y, std::vector<std::string>* spriteSheetPaths) {
	this->x = x;
	this->y = y;
	futureX = x;
	futureY = x;
	width = 107;
	height = 107;
	zIndex = 1;
	name = "ORB";

	for (std::string path : *spriteSheetPaths) {
		this->spriteSheetPaths.push_back(path);
	}

	Hitbox * hitbox = new Hitbox();
	hitbox->x = x;
	hitbox->y = x;
	hitbox->width = 107;
	hitbox->height = 107;
	hitbox->parent = this;

	hitboxes.insert(hitbox);
}

void Orb::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {
	if (currentInputs->find(InputType::UP_ARROW) != currentInputs->end()) {
		futureY -= 4;
	}
	else if (currentInputs->find(InputType::LEFT_ARROW) != currentInputs->end()) {
		futureX -= 4;
	}
	else if (currentInputs->find(InputType::RIGHT_ARROW) != currentInputs->end()) {
		futureX += 4;
	}
	else if (currentInputs->find(InputType::DOWN_ARROW) != currentInputs->end()) {
		futureY += 4;
	}

	Hitbox* futurePosition = new Hitbox();
	futurePosition->x = futureX;
	futurePosition->y = futureY;
	futurePosition->width = width;
	futurePosition->height = height;
	futurePosition->parent = this;

	std::set<OrionEntity*> entitiesWillCollideWith = collisionMap->getCollidingEntities(futurePosition);

	std::set<OrionEntity*> walls;

	//Filter to only have walls
	std::copy_if(entitiesWillCollideWith.begin(), entitiesWillCollideWith.end(), std::inserter(walls, walls.end()), [](OrionEntity* entity) {
		return dynamic_cast<Wall*>(entity) != nullptr;
		});

	std::set<OrionEntity*> trueCollisions;

	std::copy_if(walls.begin(), walls.end(), std::inserter(trueCollisions, trueCollisions.end()), [futurePosition](OrionEntity* entity) {
		return entity->isCollidingWith(futurePosition);
		});

	if (trueCollisions.size() >= 1) {
		futureX = x;
		futureY = y;
	}
}

void Orb::setPosition(double xPos, double yPos) {
	futureX = xPos;
	futureY = yPos;
}

void Orb::enactStateChanges() {
	double differenceX = futureX - x;
	double differenceY = futureY - y;

	x = futureX;
	y = futureY;

	for (Hitbox* hitbox : hitboxes) {
		hitbox->x += differenceX;
		hitbox->y += differenceY;
	}
}