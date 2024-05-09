#pragma once

#ifdef __linux__
#include <thread>
typedef std::thread ldds_task;
#else
#include "port/freertos/ldds_task.h"
typedef ldds_frtos_task ldds_task;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 任务句柄
 */
typedef void* ldds_task_t;

/**
 * @brief 任务入口函数原型
 */
typedef void (*ldds_task_entry_t)(void*);

/**
 * @brief 创建任务对象，默认值：name="ldds_task", param=任务对象指针, stack_size=2048, priority=15
 * @return 返回任务句柄，NULL失败
 */
ldds_task_t ldds_task_new(void);

/**
 * @brief 释放任务对象
 * @param task任务句柄
 */
void ldds_task_free(ldds_task_t task);

/**
 * @brief 设置任务入口函数
 * @param task任务句柄
 * @param entry任务句柄
 * @return true成功，false失败
 */
bool ldds_task_set_entry(ldds_task_t task, ldds_task_entry_t entry);

/**
 * @brief 设置任务名称
 * @param task任务句柄
 * @param name任务名称
 * @return true成功，false失败
 */
bool ldds_task_set_name(ldds_task_t task, const char *name="ldds_task");

/**
 * @brief 设置任务栈空间大小
 * @param task任务句柄
 * @param size栈空间大小，单位字节，默认为2048
 * @return true成功，false失败
 */
bool ldds_task_set_stack_size(ldds_task_t task, int size=2048);

/**
 * @brief 设置任务优先级
 * @param task任务句柄
 * @param priority任务优先级，默认15
 * @return true成功，false失败
 */
bool ldds_task_set_priority(ldds_task_t task, int priority=15);

/**
 * @brief 运行任务
 * @param task任务句柄
 * @return true成功，false失败
 */
bool ldds_task_run(ldds_task_t task);

/**
 * @brief 当前任务延时
 * @param millisecond延时时间，单位毫秒
 */
void ldds_task_delay(int millisecond);

#ifdef __cplusplus
}
#endif
