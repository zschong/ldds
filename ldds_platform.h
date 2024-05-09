#pragma once

#include <sstream>
#include <string>
#include "ldds_bus.h"

class ldds_platform {
private:
    ldds_syncm<char*,ldds_bus> _router;

public:
    ldds_platform(void) {
        // printf("%s, %p\n", __func__, this);
    }

    /**
     * @brief 订阅主题
     */
    bool sub(const char *topic, ldds_node *node, ldds_msg_handler_t handler) {
        auto key = (char*)ldds_msgcc::get_key(topic);
        ldds_bus &bus = _router[key];

        bus.set_name(topic);

        if (bus.sub(node)) {
            return node->sub(key, handler);
        }

        return false;
    }

    /**
     * @brief 退订主题
     */
    bool unsub(const char *topic, ldds_node *node, ldds_msg_handler_t handler) {
        if (NULL == node) {
            return false;
        }

        auto key = (char*)ldds_msgcc::get_key(topic);

        // 把消息处理函数从消息队退订阅列表中移除
        node->unsub(key, handler);

        ldds_bus *bus = (ldds_bus*)_router.find(key);

        if (NULL == bus) {
            return false;
        }

        // 把消息队列移出订阅列表
        if (bus->unsub(node) == false) {
            return false;
        }

        // 主题下无订阅者，删除主题
        if (bus->empty()) {
            _router.erase(key);
        }

        return true;
    }

    /**
     * @brief 发布消息
     */
    bool pub(ldds_msg_t msg) {
        if (ldds_msg_valid(msg) == false) {
            return false;
        }

        char* key = (char*)ldds_msg_topic(msg);
        ldds_bus *bus = (ldds_bus*)_router.find(key);

        if (bus) {
            return bus->pub(msg);
        }

        return false;
    }

    void show(std::ostringstream &oss, int level=0, int step=4) const {
        std::string indent(level*step, ' ');
        std::string subind((level+1)*step, ' ');

        oss << indent << "ldds_platform: {" << std::endl;
        _router.foreach([&oss, level, step, subind](char* const topic, ldds_bus &bus) {
            oss << subind << "[" << std::endl;
            bus.show(oss, level+2, step);
            oss << subind << "]" << std::endl;
        });
        oss << indent << "}" << std::endl;
    }
};
