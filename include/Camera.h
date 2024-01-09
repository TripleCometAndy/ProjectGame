#pragma once

#include "OrionEntity.h"
#include "InputType.h"

class Camera : public OrionEntity {
public:
	Camera();

	void handleStateChanges(std::set<InputType>* currentInputs, std::set<JoystickInput *> * joystickInputs, CollisionMap * collisionMap, int dt);
	void enactStateChanges();
	void show(int shaderProgram);
};