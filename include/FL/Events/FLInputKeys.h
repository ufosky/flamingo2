
// Action Types
//      Powers of 2 are "downs"
//      (Powers of 2)+1 are "ups"
//      (Powers of 2)+2 are "holds"
//      (Powers of 2)+3 are the same as "downs" (removed Frame after)
//      (Powers of 2)+4 are "ups" (removed Frame after)
//      (Powers of 2)+5 are the same as "holds" (removed Frame after)
#define NOEVENT             0
#define QUIT                -2
#define VIDEOEXPOSE         -3
#define VIDEORESIZE         -5
#define KEYDOWN             8
#define KEYUP               9
#define KEYHOLD             10
#define MOUSEMOTION         15
#define MOUSEBUTTONDOWN     16
#define MOUSEBUTTONUP       17
#define MOUSEBUTTONHOLD     18
#define SCROLLWHEEL         MOUSEBUTTONDOWN
#define TIMERSTART          32
#define TIMEREND            33
#define TIMERTICK           34
                            
#define JOYAXISMOTION       0
#define JOYBALLMOTION       0
#define JOYHATMOTION        0
#define JOYBUTTONUP         0
#define JOYBUTTONDOWN       0

// Action Keys
#define K_NONE              -1
#define MB_1                -11
#define MB_2                -12
#define MB_3                -13
#define MS_DOWN             -14
#define MS_UP               -15
#define M_MOTION            -16

