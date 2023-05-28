#include "OptionsLoader.h"
#include "OrionLoop.h"
#include "HardwareAbstractionLayer.h"
#include "SDLHandler.h"
#include "Timer.h"
#include "TimerImpl.h"
#include "EventHandlerImpl.h"
#include "EventHandlerWrite.h"
#include "EventHandlerRead.h"
#include "RendererImpl.h"

#include <iostream>


int main(int argc, char** argv)
{
    Options* options = getOptions("Options.txt");
    HardwareAbstractionLayer* sdlHandler = new SDLHandler();

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
        eventHandler = new EventHandlerImpl(sdlHandler);
    }

    
    Timer* timer = new TimerImpl(sdlHandler);
    Renderer* renderer = new RendererImpl();

    OrionLoop* orionLoop = new OrionLoop(options, sdlHandler, timer, eventHandler, renderer);
    orionLoop->initialize();
    orionLoop->execute();

    return 0;
}