#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <sstream>
#include <iostream>
#include "ldds.h"

#define MQ_LIMIT 32
#define TOPIC_LIMIT 16 

/**
 * @brief 消息模型
 * 模块a[订阅、发布]
 * 模块b[订阅、发布]
 * 模块c[订阅、发布]
 * ...
 * 模块x[订阅、发布]
 */

// 模块：消息队列线程，模拟模块化
std::thread mq_thread(ldds_node_t node) {
    while (true) {
        int msg_count = ldds_dispatch(node);

        if (msg_count > 0) {
            printf("msg_count=%d\n", msg_count);
        }

        usleep(1000);
    }
}

// 事件：消息处理函数，模拟接收到消息处理实例
void handler1(ldds_msg_t msg) {
    auto id = std::this_thread::get_id();
    std::cout << "thread:" << id << ", " << __func__ << std::endl;
    ldds_msg_print(msg, printf);
}

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

int main(void) {
    ldds_node_t node[MQ_LIMIT] = {NULL};

    for (int i = 0; i < ARRAY_SIZE(node); i++) {
        node[i] = ldds_new();
    }

    // 订阅：模拟订阅主题
    for (int i = 0; i < ARRAY_SIZE(node); i++) {
        char topic[MQ_LIMIT];

        snprintf(topic, sizeof(topic), "topic.%03d", i%TOPIC_LIMIT);

        ldds_sub(node[i], topic, handler1);

        std::thread(mq_thread, std::ref(node[i])).detach();
    }

    // 发布：模拟消息发布, 消息随机生成
    while (1) {
        char topic[MQ_LIMIT];
        char payload[MQ_LIMIT];
        int event = random() % 1000;

        snprintf(topic, sizeof(topic), "topic.%03d", event%TOPIC_LIMIT);
        snprintf(payload, sizeof(payload), "payload %04d", event);

        ldds_pub(topic, payload, strlen(payload));
        usleep(1000);
        ldds_debug(printf);
    }

    return 0;
}
