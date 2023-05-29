#pragma once

#include "Hitbox.h"

#include <set>
#include <utility>

class CollisionMap {
private:
	int width;
	int height;
	int trueWidth;
	int trueHeight;
	int sizeOfCells;

	std::set<Hitbox *>** cells;

	int getIndexInMap(double num, double max);

public:
	CollisionMap(int trueWidth, int trueHeight, int minSizeOfCell);

	std::set<OrionEntity *> getCollidingEntities(Hitbox * hitbox);
	void addHitboxes(std::set<Hitbox*>* hitboxes);
	void updateEntityPosition(std::set<Hitbox*>* hitboxes);
	void clearHitbox(Hitbox* hitbox);
};