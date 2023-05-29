#pragma once

#include "EntityManager.h"

class EventHandler {
public:
	EventHandler();

	virtual void handleEvents(bool* shouldQuit, EntityManager * entityManager) = 0;
};