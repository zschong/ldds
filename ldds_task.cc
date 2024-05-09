#include "ldds_task.h"

#ifdef __linux__
ldds_task_t ldds_task_new(void) {return  (ldds_task_t)new ldds_task;}
void ldds_task_free(ldds_task_t task) {delete (ldds_task *)task;}
bool ldds_task_set_entry(ldds_task_t task, ldds_task_entry_t entry) {return true;}
bool ldds_task_set_name(ldds_task_t task, const char *name) {return true;}
bool ldds_task_set_stack_size(ldds_task_t task, int size) {return true;}
bool ldds_task_set_priority(ldds_task_t task, int priority) {return true;}
bool ldds_task_run(ldds_task_t task) {return true;}
void ldds_task_delay(int millisecond) { std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));}
#else
/**
 * @brief 创建任务对象，默认值：name="ldds_task", param=任务对象指针, stack_size=2048, priority=15
 */
ldds_task_t ldds_task_new(void) {
    return  (ldds_task_t)new ldds_task;
}

/**
 * @brief 释放任务对象
 */
void ldds_task_free(ldds_task_t task) {
    delete (ldds_task *)task;
}

/**
 * @brief 设置任务入口函数
 */
bool ldds_task_set_entry(ldds_task_t task, ldds_task_entry_t entry) {
    if (NULL == task) {
        return false;
    }

    ((ldds_task *)task)->set_entry(entry);
    return true;
}

/**
 * @brief 设置任务名称
 */
bool ldds_task_set_name(ldds_task_t task, const char *name="ldds_task") {
    if (NULL == task) {
        return false;
    }

    ((ldds_task *)task)->set_name(name);
    return true;
}

/**
 * @brief 设置任务栈空间大小
 */
bool ldds_task_set_stack_size(ldds_task_t task, int size=2048) {
    if (NULL == task) {
        return false;
    }

    ((ldds_task *)task)->set_stack(size);
    return true;
}

/**
 * @brief 设置任务优先级
 */
bool ldds_task_set_priority(ldds_task_t task, int priority=15) {
    if (NULL == task) {
        return false;
    }

    ((ldds_task *)task)->set_priority(priority);
    return true;
}
/**
 * @brief 运行任务
 */
bool ldds_task_run(ldds_task_t task) {
    if (NULL == task) {
        return false;
    }

    ((ldds_task *)task)->run();
    return true;
}

/**
 * @brief 当前任务延时
 */
void ldds_task_delay(int millisecond) {
    ldds_task::delay(millisecond);
}
#endif