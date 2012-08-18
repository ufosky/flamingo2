
#ifndef CLOCK_H_
#define CLOCK_H_

#include <time.h>

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC 1000
#endif

#define SECONDS(t) (t / (double)CLOCKS_PER_SEC)
#define TICKS(s) ((int)(s * CLOCKS_PER_SEC))

#define CLOCK_PAUSED 1


class Clock {
    public:
        Clock();
        ~Clock();

        void Sync();

        long int GetTime();
        int GetFPS();
        
        bool IsPaused();
        void Pause();
        void Resume();

    private:
        long int current, last, offset;
        int fps;

        int flags;
};

#endif

