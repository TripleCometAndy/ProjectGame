#include "OptionsLoader.h"
#include "OrionLoop.h"
#include "EventHandlerImpl.h"
#include "EventHandlerWrite.h"
#include "EventHandlerRead.h"

#include <iostream>


int main(int argc, char** argv)
{
    Options* options = getOptions("../Options.txt");

    EventHandler* eventHandler;
    if (options->areEventsWrittenToFile) {
        std::cout << "WRITING TO FILE" << std::endl;
        std::cout << options->eventHandlerWritePath << std::endl;

        eventHandler = new EventHandlerWrite(options->eventHandlerWritePath);
    }
    else if (options->areEventsReadFromFile) {
        std::cout << "READING FROM FILE" << std::endl;
        
        eventHandler = new EventHandlerRead(options->eventHandlerReadPath);
    }
    else {
        std::cout << "NOT WRITING TO FILE" << std::endl;
        eventHandler = new EventHandlerImpl();
    }


    OrionLoop* orionLoop = new OrionLoop(options, eventHandler);
    orionLoop->initialize();
    orionLoop->execute();

    return 0;
}