
#include "EventHandlerWrite.h"
#include "InputType.h"

#include <set>

EventHandlerWrite::EventHandlerWrite(std::string pathToInputs) {
	currentFrame = 0;

	//Open filestream
    fs.open(pathToInputs.c_str(), std::ofstream::out | std::ofstream::trunc);
}

void EventHandlerWrite::handleEvents(bool* shouldQuit, EntityManager* entityManager, GLFWwindow * window) {
    
}

void EventHandlerWrite::writeInputsToFile(std::set<InputType>* events) {
    fs << currentFrame;
    fs << ":";
    
    for (InputType event : *events) {
        fs << event;
        fs << ",";
    }
    
    fs << "\n";
}