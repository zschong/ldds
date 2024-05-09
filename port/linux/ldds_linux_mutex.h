#pragma once

#include <thread>
#include <chrono>
#include <mutex>

class ldds_linux_mutex {
private:
    std::mutex _mutex;

public:
    ldds_linux_mutex(void) {
        // printf("%s, %p\n", __func__, this);
    }

    void lock(void) {
        _mutex.lock();
    }

    bool trylock(uint64_t timeout_ms) {
        for (uint64_t i = 0; i < timeout_ms; i++) {
            if (_mutex.try_lock()) {
                return true;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        return false;
    }

    void unlock(void) {
        _mutex.unlock();
    }
};
