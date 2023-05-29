#include "OrionEntity.h"
#include "IOException.h"
#include "Hitbox.h"

#include <iostream>

OrionEntity::OrionEntity() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
}

void OrionEntity::show()
{
}

std::set<Hitbox *>* OrionEntity::getHitboxes() {
	std::set<Hitbox *>* copies = new std::set<Hitbox *>();
	
	for (Hitbox * hitbox : hitboxes) {
		copies->insert(hitbox);
	}

	return copies;
}

int OrionEntity::getZIndex() {
	return zIndex;
}

bool OrionEntity::isCollidingWith(Hitbox* hitbox) {
	bool isCollidingWith = false;

	for (Hitbox* h : hitboxes) {
		isCollidingWith = h->isColliding(hitbox);

		if (isCollidingWith) {
			break;
		}
	}

	return isCollidingWith;
}

std::string OrionEntity::getName() {
	return name;
}

double OrionEntity::getX() {
	return x;
}

double OrionEntity::getY() {
	return y;
}