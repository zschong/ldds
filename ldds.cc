#include "ldds_platform.h"
#include "ldds_node.h"
#include "ldds_platform.h"
#include "ldds.h"

/**
 * @brief 获取消息队列管理实体
 */
static ldds_platform* _ldds_instance(void) {
    static ldds_platform *platform = NULL;

    if (platform) {
        return platform;
    }

    platform = new ldds_platform;
    return platform;
}

/**
 * @brief 创建消息队列
 */
ldds_node_t ldds_new(void) {
    return (ldds_node_t)(new ldds_node);
}

/**
 * @brief 释放消息队列内存
 */
void ldds_free(ldds_node_t node) {
    if (NULL == node) {
        return;
    }

    delete (ldds_node*)node;
}

/**
 * @brief 释放消息队列内存
 */
int ldds_dispatch(ldds_node_t node) {
    if (NULL == node) {
        return -1;
    }

    return ((ldds_node*)node)->dispatch();
}


/**
 * @brief 订阅主题
 */
bool ldds_sub(ldds_node_t node, const char *topic, ldds_msg_handler_t handler) {
    ldds_platform *p = _ldds_instance();

    if (NULL == p) {
        return false;
    }

    return p->sub(topic, (ldds_node*)node, handler);
}

/**
 * @brief 退订主题
 */
bool ldds_unsub(ldds_node_t node, const char *topic, ldds_msg_handler_t handler) {
    ldds_platform *p = _ldds_instance();

    if (NULL == p) {
        return false;
    }

    return p->unsub(topic, (ldds_node*)node, handler);
}

/**
 * @brief 发布消息
 */
bool ldds_pub(const char *topic, void *data, uint32_t len) {
    ldds_platform *p = _ldds_instance();

    if (NULL == p) {
        return false;
    }
    ldds_msg_t msg = ldds_msg_create(topic, data, len);

    if (NULL == msg) {
        return false;
    }

    return p->pub(msg);
}

/**
 * @brief 打印消息队列调试信息
 */
void ldds_debug(int(printf)(const char*,...)) {
    if (printf) {
        ldds_platform *p = _ldds_instance();
        std::ostringstream oss;
        p->show(oss);
        printf("%s\n", oss.str().data());
    }
}
