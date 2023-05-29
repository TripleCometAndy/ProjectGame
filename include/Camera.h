#pragma once

#include "OrionEntity.h"
#include "InputType.h"

class Camera : public OrionEntity {
public:
	Camera();

	void handleStateChanges(std::set<InputType>* currentInputs, CollisionMap * collisionMap);
	void enactStateChanges();
};