#pragma once

#include "EventHandler.h"

#include <fstream>

class EventHandlerWrite : public EventHandler {
private:
	std::ofstream fs;
	int currentFrame;

	void writeInputsToFile(std::set<InputType>* events);
public:
	EventHandlerWrite(std::string pathToInputs);
	void handleEvents(bool* shouldQuit, EntityManager* entityManager);
};