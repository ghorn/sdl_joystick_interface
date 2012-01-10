// run_realtime.c
// (c) 2011, Greg Horn

#include "run_realtime.h"

#include <unistd.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

static uint64_t usSinceEpoch()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);  
    return ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
}

void run_realtime(double dt){
    uint64_t dt_us = (uint64_t)(dt*1.0e6);
    static uint64_t us_old = 0;

    uint64_t us_now = usSinceEpoch();
    uint64_t us_next = us_old + dt_us;
    
    if (us_next > us_now){
        // if we have time to spare, set alarm clock
        us_old = us_next;
        usleep(us_next - us_now);
    } else {
        // if we're running late, do not wait
        us_old = us_now;
    }
}
