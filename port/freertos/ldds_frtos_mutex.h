#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h" 

class ldds_frtos_mutex {
private:
    SemaphoreHandle_t _semaphore;
public:
    ldds_frtos_mutex(void) {
        _semaphore = xSemaphoreCreateBinary();
        if (_semaphore) {
            xSemaphoreGive(_semaphore);
        }
    }

    ~ldds_frtos_mutex(void) {
        if (_semaphore) {
            xSemaphoreGive(_semaphore);
            vSemaphoreDelete(_semaphore);
        }
    }

    /**
     * @brief 尝试加锁
     */
    bool trylock(int timeout_ms) {
        if (NULL == _semaphore) {
            return false;
        }

        xSemaphoreTake(_semaphore, timeout_ms / portTICK_PERIOD_MS);
        return true;
    }

    /**
     * @brief 加锁
     */
    void lock(void) {
        if (_semaphore) {
            xSemaphoreTake(_semaphore, portMAX_DELAY);
        }
    }

    /**
     * @brief 解锁
     */
    void unlock(void) {
        if (_semaphore) {
            xSemaphoreGive(_semaphore);
        }
    }
};

