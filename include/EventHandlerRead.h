#pragma once

#include "EventHandler.h"

#include <unordered_map>
#include <set>

class EventHandlerRead : public EventHandler {
private:
	std::unordered_map<int, std::set<InputType>> readInputs;
	int currentFrame;
public:
	EventHandlerRead(std::string pathToInputs);
	void handleEvents(bool* shouldQuit, EntityManager* entityManager, GLFWwindow * window);
};