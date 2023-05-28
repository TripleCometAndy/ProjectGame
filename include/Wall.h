#pragma once

#include "OrionEntity.h"
#include "InputType.h"

class Wall : public OrionEntity {
public:
	Wall(double x, double y, int width, int height, std::vector<std::string>* spriteSheetPaths);

	void handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap);
	void enactStateChanges();
	void setPosition(double xPos, double yPos);
};