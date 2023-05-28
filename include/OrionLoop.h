#pragma once

#include "EventHandler.h"
#include "Options.h"


class OrionLoop {
private:
	unsigned int FPS;
	EventHandler* eventHandler;
	EntityManager* entityManager;

public:
	OrionLoop(Options * options, EventHandler * eventHandler);

	void initialize();
	void execute();
	int getEntityX(std::string entityName);
	int getEntityY(std::string entityName);
};