#include "Wall.h"
#include "Hitbox.h"
#include <iostream>

Wall::Wall(double x, double y, int width, int height, std::vector<std::string>* spriteSheetPaths) {
	this->x = x;
	this->y = y;
	futureX = x;
	futureY = y;
	this->width = width;
	this->height = height;
	zIndex = 2;
	name = "WALL";

	for (std::string path : *spriteSheetPaths) {
		this->spriteSheetPaths.push_back(path);
	}

	Hitbox* hitbox = new Hitbox();
	hitbox->x = x;
	hitbox->y = y;
	hitbox->width = width;
	hitbox->height = height;
	hitbox->parent = this;

	hitboxes.insert(hitbox);
}

void Wall::handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) {
}

void Wall::setPosition(double xPos, double yPos) {
}

void Wall::enactStateChanges() {
}