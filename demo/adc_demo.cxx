#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <sstream>
#include <iostream>
#include "ldds_duration.h"
#include "ldds_task.h"
#include "ldds.h"

/**
 * @brief 模拟两个adc读数据和处理数据业务分布式开发流程
 * @param adc1_read 数据采集模块
 * @param adc2_read 数据采集模块
 * @param node_main 数据处理模块
 * @param ldds_node_t 消息总线订阅者节点，负责订阅消息，注册消息处理函数，颁发消息到处理函数
 */

// 模块：监听消息到来，并处理消息
void node_main(ldds_node_t node) {
    while (1) {
        int msg_count = ldds_dispatch(node);

        if (msg_count > 0) {
            printf("msg_count=%d\n", msg_count);
        }

        ldds_task_delay(100);
    }
}

int _get_thread_id(void) {
    auto id = std::this_thread::get_id();
    return std::hash<std::thread::id>()(id);
}

void on_adc1_change(ldds_msg_t msg) {
    // 处理ADC1数据变化事件
    ldds_msg_print(msg, printf);
    printf("%x: %s: %d\n", _get_thread_id(), __func__, *(int*)ldds_msg_data(msg));
}

void on_adc2_change(ldds_msg_t msg) {
    // 处理ADC2数据变化事件
    ldds_msg_print(msg, printf);
    printf("%x: %s: %d\n", _get_thread_id(), __func__, *(int*)ldds_msg_data(msg));
}

// 订阅ADC1_change主题
void sub_adc1(void) {
    ldds_node_t node = ldds_new();

    ldds_sub(node, "ADC1_change", on_adc1_change);
    // ldds_sub(node, "ADC2_change", on_adc2_change);
    std::thread(node_main, node).detach();
}

// 订阅ADC2_change主题
void sub_adc2(void) {
    ldds_node_t node = ldds_new();

    // ldds_sub(node, "ADC1_change", on_adc1_change);
    ldds_sub(node, "ADC2_change", on_adc2_change);
    std::thread(node_main, node).detach();
}

// 模拟adc1驱动，读取数据
void adc1_reader(void) {
    static int adc_value = 0;
    
    int tmp = random() % 4096;
    if (tmp != adc_value) {
        adc_value = tmp;
        ldds_pub("ADC1_change", &adc_value, sizeof(adc_value));
    }
}

// 模拟adc2驱动，读取数据
void adc2_reader(void) {
    static int adc_value = 0;
    
    int tmp = random() % 4096;
    if (tmp != adc_value) {
        adc_value = tmp;
        ldds_pub("ADC2_change", &adc_value, sizeof(adc_value));
    }
}

int main(void) {
    sub_adc1();
    sub_adc2();

    ldds_task_delay(1000);

    while (1) {
        adc1_reader();
        adc2_reader();
        ldds_task_delay(1000);
        // ldds_debug(printf);
    }

    return 0;
}
