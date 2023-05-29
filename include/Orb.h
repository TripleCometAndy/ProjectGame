#pragma once

#include "OrionEntity.h"
#include "InputType.h"

class Orb : public OrionEntity {
public:
	Orb(double x, double y, std::vector<std::string>* spriteSheetPaths);

	void handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap);
	void enactStateChanges();
	void setPosition(double xPos, double yPos);
};