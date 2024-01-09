#pragma once

#include "OrionEntity.h"
#include "InputType.h"
#include "CollisionMap.h"
#include "JoystickInput.h"

#include <vector>
#include <set>

class EntityManager {
private:
	std::vector<OrionEntity*> entities;
	std::set<InputType>* currentInputs;
	std::set<JoystickInput *> * currentJoystickInputs;
	CollisionMap* collisionMap;
public:
	EntityManager(CollisionMap * collisionMap);
	void addEntity(OrionEntity* entity);
	void showAll(int shaderProgram);
	void setInputs(std::set<InputType>* events, std::set<JoystickInput *> * joystickInputs);
	void handleStateChanges(int dt);
	void enactStateChanges();
	int getEntityX(std::string entityName);
	int getEntityY(std::string entityName);
};