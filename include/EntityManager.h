#pragma once

#include "OrionEntity.h"
#include "InputType.h"
#include "CollisionMap.h"

#include <vector>
#include <set>

class EntityManager {
private:
	std::vector<OrionEntity*> entities;
	std::set<InputType>* currentInputs;
	CollisionMap* collisionMap;
public:
	EntityManager(CollisionMap * collisionMap);
	void addEntity(OrionEntity* entity);
	void showAll();
	void setInputs(std::set<InputType>* events);
	void handleStateChanges();
	void enactStateChanges();
	int getEntityX(std::string entityName);
	int getEntityY(std::string entityName);
};