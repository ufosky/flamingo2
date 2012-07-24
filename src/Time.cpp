
#include "FL/Time.h"

Clock::Clock() {
    offset = (long int)clock();
    current = 0;
    last = 0;
    fps = 0;
    flags = 0;
}

Clock::~Clock() {

}

void Clock::Sync() {

    if (flags && CLOCK_PAUSED) {
        offset = (long int)clock() - current;
    } else {
        last = current;
        current = (long int)clock() - offset;
        
        if (current - last > 0) {
            fps = (fps + (CLOCKS_PER_SEC / (1.0 * current - last))) / 2.0;    
        }
    }
}

long int Clock::GetTime() {
    return current;
}

int Clock::GetFPS() {
    return fps;
}

void Clock::Pause() {
    flags |= CLOCK_PAUSED;
}

void Clock::Resume() {
    flags &= ~CLOCK_PAUSED;
}

bool Clock::IsPaused() {
    return flags && CLOCK_PAUSED;
}

