# ldds

## 介绍
- Local DDS，简化版DDS，实现MCU本地数据分发服务；
- 兼容linux、windows、mac、freertos等支持标准c++11容器库的系统；
- 实现类以ROS系统的开发模式，简化软件的设计开发流程，可以支撑不同规范的团队协作开发；
- 封装了c接口，方便不熟悉c++的单片机开发者使用；
- 已经在esp32和linux平台验证使用；
###  框架
![image](https://github.com/zschong/ldds/assets/26220314/135bc8c5-2948-41c2-8f3f-bbf1fc4e8a71)

### 主题管理
每个主题有一个管理器对象，管理本主题下的订阅者节点。
![image](https://github.com/zschong/ldds/assets/26220314/21916fe0-4b50-4cdf-9387-62d09a3e6f87)
### 节点管理（订阅）
模块创建节点，订阅主题时向消息框架实现主题与节点的绑定。节点内部有一个主题管理表，用于主题与消息处理函数的绑定。
![image](https://github.com/zschong/ldds/assets/26220314/96a3b0af-ec5d-4943-b919-3e0339d3ef1f)

### 消息分发（发布）
![image](https://github.com/zschong/ldds/assets/26220314/40d85d6e-78c9-4e49-8666-c6c832063b55)

## LDDS拓扑模型
```cpp
/**
 * @brief 分布式消息框架拓扑
 * @param platform消息平台，消息总线挂载在消息平台上
 * @param bus消息总线,消息总线每个主题对应一条消息总线
 * @param node角色节点，订阅主题，挂载到消息总线上
 * @param msg消息体，携带topic信息和数据载荷
 * @param handler消息处理函数，收到到msg时执行
 * platform
 *     |--bus1(topic.001)
 *         |--node1
 *              |--[msg1, msg2, msg3,...]
 *              |--{topic.001, handler1}
 *              |--{topic.002, handler2}
 *         |--node2
 *              |--[msg1, msg2, msg3,...]
 *              |--{topic.001, handler1}
 *              |--{topic.003, handler3}
 *     |--bus2(topic.002)
 *         |--node1
 *              |--[]
 *              |--{topic.001, handler1}
 *              |--{topic.003, handler3}
 *     |--bus3(topic.003)
 *         |--node2
 *              |--[msgA, msgB, msgC, ...]
 *              |--{topic.001, handler1}
 *              |--{topic.003, handler3}
 */
```

## 分布式消息中间件实例演示
```cpp
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <thread>
#include <sstream>
#include <iostream>
#include "ldds.h"

/**
 * @brief 消息模型
 * 模块a[订阅、发布]
 * 模块b[订阅、发布]
 * 模块c[订阅、发布]
 * ...
 * 模块x[订阅、发布]
 */

// 模块：监听消息到来，并处理消息
std::thread node_listener(ldds_node_t node) {
    while (true) {
        int msg_count = ldds_dispatch(node);

        if (msg_count > 0) {
            printf("msg_count=%d\n", msg_count);
        }

        usleep(1000);
    }
}

void on_adc1_change(ldds_msg_t msg) {
    // 处理ADC1数据变化事件
}

void on_adc2_change(ldds_msg_t msg) {
    // 处理ADC2数据变化事件
}

// 订阅ADC1_change主题
void sub_adc1(void) {
    ldds_node_t node = ldds_new();
    ldds_sub(ADC1_node, "ADC1_change", on_adc1_change);

    std::thread(node_listener, std::ref(ADC1_node)).detach();
}

// 订阅ADC2_change主题
void sub_adc2(void) {
    ldds_node_t node = ldds_new();
    ldds_sub(ADC2_node, "ADC2_change", on_adc2_change);

    std::thread(node_listener, std::ref(ADC2_node)).detach();
}

// 模拟adc1驱动，读取数据
void adc1_reader(void) {
    static int adc_value = 0;
    
    int tmp = random() % 4096;
    if (tmp != adc_value) {
        adc_value = tmp;
        ldds_pub("ADC1_change", &adc_value, strlen(adc_value));
    }
}

// 模拟adc2驱动，读取数据
void adc2_reader(void) {
    static int adc_value = 0;
    
    int tmp = random() % 4096;
    if (tmp != adc_value) {
        adc_value = tmp;
        ldds_pub("ADC2_change", &adc_value, strlen(adc_value));
    }
}

int main(void) {
    sub_adc1();
    sub_adc2();

    while (1) {
        adc1_reader();
        adc2_reader();
        ldds_task_delay(1000 * 1000);
    }

    return 0;
}
```
```shell
.
├── CMakeLists.txt              # idf-5.2.1
├── component.mk                # idf-4.3.5
├── demo                        # 演示用例
│   ├── duration_demo.cxx       # 持续时间实例演示
│   ├── hex_demo.cxx            # 十六进制实例演示
│   ├── ldds_demo.cxx            # 消息总线实例演示
│   ├── makefile                # linux下编译管理
│   ├── msg_demo.cxx            # 消息体实例演示
│   ├── mutex_demo.cxx          # 互斥锁实例演示
│   ├── node_demo.cxx           # 消息框架角色节点实例演示
│   ├── payload_demo.cxx        # 消息载荷实例演示
│   ├── platform_demo.cxx       # 消息平台实例演示
│   ├── rtti_demo.cxx           # 类型信息实例演示
│   ├── syncm_demo.cxx          # 同步kv表实例演示
│   ├── syncq_demo.cxx          # 同步队列实例演示
│   ├── time_demo.cxx           # 时间实例演示
│   └── bus_demo.cxx            # 消息总线实例演示
├── ldds.cc          # 消息总线实现
├── ldds.h           # 消息总线头文件
├── ldds_bus.h       # 消息总线头文件
├── ldds_cmutex.cc   # 互斥锁实现
├── ldds_cmutex.h    # 互斥锁头文件
├── ldds_duration.h  # 持续时间实现
├── ldds_hex.h       # 十六进制实现
├── ldds_msg.cc      # 消息体c调用封装
├── ldds_msg.h       # 消息体c调用头文件
├── ldds_msgcc.h     # 消息体c++实现
├── ldds_mutex.h     # 互斥锁头文件
├── ldds_node.h      # 消息框架角色节点头文件
├── ldds_payload.h   # 消息载荷头文件
├── ldds_platform.h  # 消息平台头文件
├── ldds_rtti.h      # 类型信息头文件
├── ldds_syncm.h     # 同步kv表头文件
├── ldds_syncq.h     # 同步队列头文件
├── ldds_task.h      # 任务头文件
├── ldds_time.h      # 时间头文件
├── makefile         # 编译libldds.a
└── port
    ├── freertos                # freertos系统兼容
    │   ├── ldds_frtos_mutex.h
    │   ├── ldds_frtos_task.h
    │   └── ldds_frtos_time.h
    └── linux                   # linux系统兼容
        ├── ldds_linux_mutex.h
        └── ldds_linux_time.h
```.
