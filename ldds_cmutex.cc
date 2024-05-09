#include "ldds_cmutex.h"
#include "ldds_mutex.h"



/**
 * @brief 创建互斥量
 */
ldds_cmutex_t ldds_cmutex_new(void) {
    return (ldds_cmutex_t)(new ldds_mutex);
}

/**
 * @brief 释放互斥量
 */
void ldds_cmutex_free(ldds_cmutex_t mutex) {
    if (mutex) {
        delete (ldds_mutex*)mutex;
    }
}

/**
 * @brief 尝试加锁
 */
bool ldds_cmutex_trylock(ldds_cmutex_t mutex, int timeout_ms) {
    if (mutex) {
        return ((ldds_mutex*)mutex)->trylock(timeout_ms);
    }

    return false;
}

/**
 * @brief 加锁
 */
bool ldds_cmutex_lock(ldds_cmutex_t mutex) {
    if (mutex) {
        ((ldds_mutex*)mutex)->lock();
        return true;
    }

    return false;
}

/**
 * @brief 解锁
 */
bool ldds_cmutex_unlock(ldds_cmutex_t mutex) {
    if (mutex) {
        ((ldds_mutex*)mutex)->unlock();
        return true;
    }

    return false;
}


