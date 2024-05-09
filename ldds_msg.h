#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief 消息类型定义{char *topic, void *payload, uint32_t length}
 */
typedef void* ldds_msg_t;

/**
 * @brief 消息处理函数
 * @param m消息变量
 */
typedef void (*ldds_msg_handler_t)(ldds_msg_t);

/**
 * @brief 创建消息
 * @param topic消息主题
 * @param data消息数据载荷
 * @param len消息数据载荷长度
 * @return 返回消息变量
 */
ldds_msg_t ldds_msg_create(const char *topic, const void *data, uint32_t len);

/**
 * @brief 释放消息内存
 * @param m消息变量
 */
void ldds_msg_free(ldds_msg_t m);

/**
 * @brief 创建消息副本
 * @param m消息变量
 */
ldds_msg_t ldds_msg_dup(ldds_msg_t m);

/**
 * @brief 消息有效判断
 */
bool ldds_msg_valid(ldds_msg_t m);

/**
 * @brief 设置消息主题
 * @param topic消息主题
 * @return 成功返回true，失败返回false
 */
bool ldds_set_topic(ldds_msg_t m, const char *topic);

/**
 * @brief 设置消息载荷
 * @param data载荷数据
 * @param len载荷长度
 * @return 成功返回true，失败返回false
 */
bool ldds_set_data(ldds_msg_t m, const void *data, uint32_t len);

/**
 * @brief 填充消息载荷
 * @param c填充值
 * @param len填充长度
 * @return 成功返回true，失败返回false
 */
bool ldds_msg_fill(ldds_msg_t m, uint8_t c, uint32_t len);

/**
 * @brief 获取消息主题
 * @param m消息变量
 * @return 成功返回主题指针，失败返回NULL
 */
const char* ldds_msg_topic(ldds_msg_t m);

/**
 * @brief 获取消息数据
 * @param m消息变量
 * @return 成功返回数据指针，失败返回NULL
 */
const void* ldds_msg_data(ldds_msg_t m);

/**
 * @brief 获取消息数据长度
 * @param m消息变量
 * @return 成功返回数据长度，失败返回0
 */
uint32_t ldds_msg_length(ldds_msg_t m);

/**
 * @brief 打印消息详情
 * @param m消息变量
 */
void ldds_msg_print(ldds_msg_t m, int (*printf)(const char*,...));

#ifdef __cplusplus
}
#endif
