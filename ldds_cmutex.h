#pragma once

#ifdef __cpluspus
extern "C" {
#endif

typedef void* ldds_cmutex_t;

/**
 * @brief 创建互斥量
 */
ldds_cmutex_t ldds_cmutex_new(void);

/**
 * @brief 释放互斥量
 * @param mutex互斥量
 */
void ldds_cmutex_free(ldds_cmutex_t mutex);

/**
 * @brief 尝试加锁
 * @param mutex互斥量
 * @param timeout_ms等待获取锁
 * @return true上锁成功，false上锁失败
 */
bool ldds_cmutex_trylock(ldds_cmutex_t mutex, int timeout_ms);

/**
 * @brief 加锁
 * @param mutex互斥量
 * @return true上锁成功，false上锁失败
 */
bool ldds_cmutex_lock(ldds_cmutex_t mutex);

/**
 * @brief 解锁
 * @param mutex互斥量
 * @return true解锁成功，false解锁失败
 */
bool ldds_cmutex_unlock(ldds_cmutex_t mutex);

#ifdef __cpluspus
}
#endif
