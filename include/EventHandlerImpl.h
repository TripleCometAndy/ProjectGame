#pragma once

#include "EventHandler.h"

class EventHandlerImpl : public EventHandler {
private:

public:
	EventHandlerImpl();
	void handleEvents(bool* shouldQuit, EntityManager* entityManager, GLFWwindow * window);
};