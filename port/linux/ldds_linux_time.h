#pragma once
#ifdef __linux__
#include <stdint.h>
#include <time.h>


class ldds_linux_time {
private:
    struct timespec _tp;

public:
    ldds_linux_time(void) {
        boottime();
    }

    uint64_t boottime(void) {
        clock_gettime(CLOCK_BOOTTIME, &_tp);
        return unixnano_u64();
    }

    uint64_t realtime(void) {
        clock_gettime(CLOCK_REALTIME, &_tp);
        return unixnano_u64();
    }

    uint64_t monotonic(void) {
        clock_gettime(CLOCK_MONOTONIC, &_tp);
        return unixnano_u64();
    }

    uint64_t u64(void) const {
        uint64_t v = _tp.tv_sec; 

        v *= 1e9;
        v += _tp.tv_nsec;

        return v;
    }

    double f64(void) const {
        double v = _tp.tv_nsec; 

        v /= 1e9;
        v += _tp.tv_sec;

        return v;
    }

    uint64_t unixnano_u64(void) const {
        return u64();
    }

    double unixnano_f64(void) const {
        return f64();
    }
};
#endif  // __linux__