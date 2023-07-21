#include "EventHandlerRead.h"
#include "InputType.h"

#include <set>
#include <fstream>
#include <iostream>

EventHandlerRead::EventHandlerRead(std::string pathToInputs) {
    currentFrame = 0;
    std::ifstream myfile(pathToInputs);
    std::string line;
    
    while (std::getline(myfile, line)) {
        std::string frameNum = line.substr(0, line.find(':'));
        int integerFrameNum = std::stoi(frameNum);

        std::string inputs = line.substr(line.find(":") + 1, line.size());
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;

        int integerToken = 0;
        std::set<InputType> inputsForFrame;
        while ((pos = inputs.find(delimiter)) != std::string::npos) {
            token = inputs.substr(0, pos);
            integerToken = std::stoi(token);
            inputsForFrame.insert(static_cast<InputType>(integerToken));
            inputs.erase(0, pos + delimiter.length());
        }

        if (inputs.size() > 0) {
            integerToken = std::stoi(inputs);

            inputsForFrame.insert(static_cast<InputType>(integerToken));
        }

        std::pair<int, std::set<InputType>> input(integerFrameNum, inputsForFrame);

        this->readInputs.insert(input);
    }
}

void EventHandlerRead::handleEvents(bool* shouldQuit, EntityManager* entityManager, GLFWwindow * window) {

}