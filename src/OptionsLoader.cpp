#include "OptionsLoader.h"

#include <iostream>
#include <fstream>

Options* getOptions(std::string path) {
	Options* options = new Options();
	std::ifstream file(path);
	std::string temp;

	std::getline(file, temp);
	unsigned int FPS = std::stoi(temp);

	options->FPS = FPS;

	std::getline(file, temp);

	if (temp.find("EVENT_HANDLER_WRITE") != std::string::npos) {
		std::cout << "GOT HERE" << std::endl;
		int eventHandlerWriteSize = temp.size();

		std::string eventHandlerWritePath = temp.substr(19, eventHandlerWriteSize - 19);

		options->areEventsWrittenToFile = true;
		options->eventHandlerWritePath = eventHandlerWritePath;
	}
	else if (temp.find("EVENT_HANDLER_READ") != std::string::npos) {
		std::cout << "READING" << std::endl;
		int eventHandlerReadSize = temp.size();

		std::string eventHandlerReadPath = temp.substr(18, eventHandlerReadSize - 18);

		options->areEventsReadFromFile = true;
		options->eventHandlerReadPath = eventHandlerReadPath;
	}

	return options;
}