#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    bool started;
	int startTicks;

public:
    Timer();
    void start();
    int getTicks();
    int getTime();
};