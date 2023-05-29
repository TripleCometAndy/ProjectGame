#include "Timer.h"



Timer::Timer() {
    // Start the timer
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::start() {
    started = true;
    startTicks = getTime();
}

int Timer::getTicks() {
    int numTicks = 0;

    if (started) {
        numTicks = getTime() - startTicks;
    }

    return numTicks;
}

int Timer::getTime() {
    std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(currentTime - startTime).count();
}

