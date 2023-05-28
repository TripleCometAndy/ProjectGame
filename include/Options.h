#pragma once

#include <string>

struct Options {
	unsigned int FPS;
	bool areEventsWrittenToFile = false;
	std::string eventHandlerWritePath;
	bool areEventsReadFromFile = false;
	std::string eventHandlerReadPath;
};