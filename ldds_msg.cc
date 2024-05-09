#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "ldds_msg.h"
#include "ldds_msgcc.h"


/**
 * @brief 创建消息
 */
ldds_msg_t ldds_msg_create(const char *topic, const void *data, uint32_t len) {
    if (NULL == topic || NULL == data || len < 1) {
        return NULL;
    }

    ldds_msgcc *m = new ldds_msgcc(topic, data, len);

    return (ldds_msg_t)m;
}

/**
 * @brief 释放消息内存
 */
void ldds_msg_free(ldds_msg_t m) {
    if (NULL == m) {
        return;
    }

    delete (ldds_msgcc*)m;
}

/**
 * @brief 释放消息内存
 */
ldds_msg_t ldds_msg_dup(ldds_msg_t m) {
    if (NULL == m) {
        return ldds_msg_t(NULL);
    }

    ldds_msgcc *m2 = new ldds_msgcc(*(ldds_msgcc*)m);
    return (ldds_msg_t)m2;
}

/**
 * @brief 设置消息主题
 */
bool ldds_set_topic(ldds_msg_t m, const char *topic) {
    if (NULL == m) {
        return false;
    }

    return ((ldds_msgcc*)m)->set_topic(topic);
}

/**
 * @brief 设置消息载荷
 */
bool ldds_set_data(ldds_msg_t m, const void *data, uint32_t len) {
    if (NULL == m) {
        return false;
    }

    return ((ldds_msgcc*)m)->set_data(data, len);
}

/**
 * @brief 填充消息载荷
 */
bool ldds_msg_fill(ldds_msg_t m, uint8_t c, uint32_t len) {
    if (NULL == m) {
        return false;
    }

    return ((ldds_msgcc*)m)->fill(c, len);
}

/**
 * @brief 消息有效判断
 */
bool ldds_msg_valid(ldds_msg_t m) {
    if (NULL == m) {
        return false;
    }

    return ((ldds_msgcc*)m)->is_valid();
}

/**
 * @brief 获取消息主题
 */
const char* ldds_msg_topic(ldds_msg_t m) {
    if (NULL == m) {
        return NULL;
    }

    return ((ldds_msgcc*)m)->topic();
}

/**
 * @brief 获取消息数据
 */
const void* ldds_msg_data(ldds_msg_t m) {
    if (NULL == m) {
        return NULL;
    }

    return ((ldds_msgcc*)m)->data();
}

/**
 * @brief 获取消息数据长度
 * @param m消息变量
 * @return 成功返回数据长度，失败返回0
 */
uint32_t ldds_msg_length(ldds_msg_t m) {
    if (NULL == m) {
        return 0;
    }

    return ((ldds_msgcc*)m)->length();
}

/**
 * @brief 打印消息详情
 */
void ldds_msg_print(ldds_msg_t m, int (*print_func)(const char*,...)) {
    if (m && print_func) {
        std::ostringstream oss;
        ((ldds_msgcc*)m)->show(oss);
        print_func("%s", oss.str().c_str());
    }
}
