#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "ldds_msg.h"

#ifdef __cpluspluls
extern "C" {
#endif

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

/**
 * @brief 消息队列数据类型
 */
typedef void* ldds_node_t;

/**
 * @brief 创建消息队列节点
 * @return 成功返回消息队列，失败返回NULL
 */
ldds_node_t ldds_new(void);

/**
 * @brief 释放消息队列内存
 * @param node消息队列节点指针
 */
void ldds_free(ldds_node_t node);

/**
 * @brief 消息分发
 * @param node消息队列节点
 * @return 返回本次完成的分发数量，-1表示node==NULL
 */
int ldds_dispatch(ldds_node_t node);

/**
 * @brief 订阅主题
 * @param node消息队列节点
 * @param topic消息主题
 * @param handler消息处理函数
 * @return 成功返回true，失败返回false
 */
bool ldds_sub(ldds_node_t node, const char *topic, ldds_msg_handler_t handler);

/**
 * @brief 退订主题
 * @param node消息队列节点
 * @param topic消息主题
 * @param handler消息处理函数
 * @return 成功返回true，失败返回false
 */
bool ldds_unsub(ldds_node_t node, const char *topic, ldds_msg_handler_t handler);

/**
 * @brief 发布消息
 * @param topic消息主题
 * @param payload消息数据载荷
 * @param len消息数据载荷长度
 * @return 成功返回true，失败返回false
 */
bool ldds_pub(const char *topic, void *payload, uint32_t len);

/**
 * @brief 打印消息队列调试信息
 * @param printf打印函数
 */
void ldds_debug(int(printf)(const char*,...));

#ifdef __cpluspluls
}
#endif
