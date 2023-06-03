#include "CollisionMap.h"
#include "Camera.h"

#include <math.h>
#include <iostream>

CollisionMap::CollisionMap(int trueWidth, int trueHeight, int minSizeOfCell) {
	this->trueWidth = trueWidth;
	this->trueHeight = trueHeight;
	this->sizeOfCells = minSizeOfCell;

	double dWidth = trueWidth;
	double dHeight = trueHeight;

	dWidth = dWidth / minSizeOfCell;
	dHeight = dHeight / minSizeOfCell;

	width = ceil(dWidth);
	height = ceil(dHeight);
	
	cells = new std::set<Hitbox *>*[width];

	for (int i = 0; i < width; i++) {
		cells[i] = new std::set<Hitbox *>[height];
	}
}

std::set<OrionEntity*> CollisionMap::getCollidingEntities(Hitbox * hitbox) {
	//Get top left index in map
	int x1 = getIndexInMap(hitbox->x, width);
	int y1 = getIndexInMap(hitbox->y, height);
	int x2 = getIndexInMap(hitbox->x + hitbox->width, width);
	int y2 = getIndexInMap(hitbox->y + hitbox->height, height);

	std::set<OrionEntity*> collidingEntities;

	for (int i = y1; i <= y2; i++) {
		for (int j = x1; j <= x2; j++) {
			std::set<Hitbox *>& currentCell = cells[j][i];

			for (Hitbox* h : currentCell) {
				collidingEntities.insert(h->parent);
			}
		}
	}

	return collidingEntities;
}

int CollisionMap::getIndexInMap(double num, double max) {
	int temp = 0;
	int index = -1;
	for (int i = 0; i < max; i++) {
		temp += sizeOfCells;

		if (temp >= num) {
			index = i;
			break;
		}
	}

	return index;
}

void CollisionMap::addHitboxes(std::set<Hitbox*>* hitboxes) {
	for (Hitbox* hitbox : *hitboxes) {
		//Get top left index in map
		int x1 = getIndexInMap(hitbox->x, width);
		int y1 = getIndexInMap(hitbox->y, height);
		int x2 = getIndexInMap(hitbox->x + hitbox->width, width);
		int y2 = getIndexInMap(hitbox->y + hitbox->height, height);

		for (int i = y1; i <= y2; i++) {
			for (int j = x1; j <= x2; j++) {
				cells[j][i].insert(hitbox);
			}
		}
	}
}

void CollisionMap::updateEntityPosition(std::set<Hitbox*>* hitboxes) {
	for (Hitbox* hitbox : *hitboxes) {
		//Clear the map of the current hitbox
		clearHitbox(hitbox);
	}

	addHitboxes(hitboxes);
}

void CollisionMap::clearHitbox(Hitbox* hitbox) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cells[j][i].erase(hitbox);
		}
	}
}