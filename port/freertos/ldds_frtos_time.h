#pragma once
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class ldds_frtos_time {
private:
    uint64_t  _msecond;

public:
    ldds_frtos_time(void) : _msecond(0ULL) {
        boottime();
    }

    uint64_t boottime(void) {
        _msecond = xTaskGetTickCountFromISR();
        _msecond *= (1000/configTICK_RATE_HZ);
        return _msecond;
    }

    uint64_t realtime(void) {
        struct timeval now;

        gettimeofday(&now, NULL);
        _msecond  = now.tv_usec / 1000;
        _msecond += now.tv_sec;
        return _msecond;
    }

    uint64_t u64(void) const {
        return _msecond;
    }

    double f64(void) const {
        double v = _msecond; 

        v /= 1000;
        v += _msecond/1000;

        return v;
    }
};
