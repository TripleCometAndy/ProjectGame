#pragma once

#include "OrionEntity.h"

class Box : public OrionEntity {
public:
    Box();

	void handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap);
	void enactStateChanges();
	void show(int shaderProgram);
};