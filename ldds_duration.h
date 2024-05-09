#pragma once
#include "ldds_time.h"

class ldds_duration {
private:
    ldds_time _start;
    ldds_time _stop;

public:
    uint64_t start(void) {
        return _start.boottime();
    }

    uint64_t stop(void) {
        return _stop.boottime();
    }

    uint64_t u64(void) {
        return _stop.u64() - _start.u64();
    }

    double f64(void) {
        return _stop.f64() - _start.f64();
    }

    const ldds_time& start_time(void) const {
        return _start;
    }

    const ldds_time& stop_time(void) const {
        return _stop;
    }
};
