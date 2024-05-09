#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string>

typedef void(*ldds_task_entry_t)(void*);

class ldds_frtos_task {
private:
    int _stack;
    int _priority;
    std::string _name;
    ldds_task_entry_t _entry;
    TaskHandle_t _handle;
    void *_param;

public:
    /**
     * @brief 构造任务配置
     * @param entry任务入口函数
     * @param name任务名称，默认ldds_task
     * @param stack任务栈空间，默认2048
     * @param param任务参数，默认NULL
     * @param priority任务优先级，默认12
     */
    ldds_frtos_task(ldds_task_entry_t entry, const char *name="ldds_frtos_task", int stack=2048, void *param=NULL, int priority=12) {
        _entry = entry;
        _name = name;
        _stack = stack;
        _param = param;
        _priority = priority;
        _handle = NULL;
    }

    void set_entry(ldds_task_entry_t entry) { _entry = entry; }
    void set_name(const std::string &name) { _name  = name;  }
    void set_stack(int stack)              { _stack = stack; }
    void set_param(void *param)            { _param = param; }
    void set_priority(int priority)        { _priority = priority; }

    /**
     * @brief 创建任务
     * @return true成功，false失败
     */
    bool create(void) {
        if (NULL == _entry) {
            return false;
        }

        char buf[32];
        snprintf(buf, sizeof(buf), "%s-%p", _name.data(), _entry);

        xTaskCreate(_entry, buf, _stack, _param, _priority, &_handle);
        return !!_handle;
    }

    /**
     * @brief 销毁任务
     * @return true成功，false失败
     */
    bool destroy(void) {
        if (NULL == _handle) {
            return false;
        }

        vTaskDelete(_handle);
        _handle = NULL;
        return true;
    }

    /**
     * @brief 延时
     * @param millisecond毫秒数
     */
    static void delay(int millisecond) {
        vTaskDelay(millisecond / portTICK_PERIOD_MS);
    }
};
