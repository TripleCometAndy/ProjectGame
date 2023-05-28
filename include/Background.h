#pragma once

#include "OrionEntity.h"
#include "InputType.h"

class Background : public OrionEntity {
public:
	Background(std::vector<std::string>* spriteSheetPaths);

	void handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap);
	void enactStateChanges();
};