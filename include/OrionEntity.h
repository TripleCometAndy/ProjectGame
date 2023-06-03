#pragma once

#include "InputType.h"
#include "Hitbox.h"
#include "CollisionMap.h"

#include <unordered_map>
#include <vector>
#include <set>
#include <string>

class OrionEntity {
protected:
	std::vector<std::string> spriteSheetPaths;
	std::set<Hitbox *> hitboxes;
	std::string name;

	double x;
	double y;
	int width;
	int height;
	int zIndex;

	//Futures
	double futureX;
	double futureY;
	double futureWidth;
	double futureHeight;

public:
	OrionEntity();
    
	std::set<Hitbox *>* getHitboxes();
	int getZIndex();
	std::string getName();
	double getX();
	double getY();
	bool isCollidingWith(Hitbox* hitbox);

	virtual void handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap) = 0;
	virtual void enactStateChanges() = 0;
	virtual void show(int shaderProgram) = 0;
};