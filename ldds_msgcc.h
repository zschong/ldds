#pragma once

#include <unordered_map>
#include "ldds_duration.h"
#include "ldds_payload.h"
#include "ldds_syncm.h"
#include "ldds_hex.h"

/**
 * @brief 消息定义
 * @field _topic消息主题
 * @field _payload消息载荷
 */
class ldds_msgcc {
private:
    const char  *_topic;
    ldds_payload  _payload;
    ldds_duration _duration;

public:
    ldds_msgcc(void) : _topic(NULL) {}

    ldds_msgcc(const ldds_msgcc &m) :_topic(NULL) {
        set_topic(m.topic());
        set_data(m.data(), m.size());
    }

    ldds_msgcc(const char *topic, const void *data, uint32_t len) :_topic(NULL) {
        if (NULL == topic || NULL == data || len < 1) {
            return;
        }

        set_topic(topic);
        set_data(data, len);
    }

    bool is_valid(void) const {
        if (NULL == _topic) {
            return false;
        }

        return !_payload.empty();
    }

    bool set_topic(const char *topic) {
        if (NULL == topic) {
            return false;
        }

        _topic = get_key(topic);

        return true;
    }

    bool set_data(const void *data, uint32_t len) {
        return _payload.set_data(data, len);
    }

    bool fill(uint8_t c, uint32_t len) {
        _payload.fill(c, len);
        return true;
    }

    const char* topic(void) const {
        return _topic;
    }

    void* data(void) const {
        return (void*)_payload.data();
    }

    uint32_t size(void) const {
        return _payload.size();
    }

    uint32_t length(void) const {
        return _payload.length();
    }

    void show(std::ostringstream &oss) {

        _duration.stop();

        oss << "ldds_msg: {" << std::endl
            << "    .topic   = " << (_topic ? _topic : "")   << std::endl
            << "    .payload = " << ldds_hex(_payload).data() << std::endl
            << "    .length  = " << _payload.size()          << std::endl
            << "    .duration= " << _duration.f64()          <<std::endl
            << "}" << std::endl;
    }

    static const char *get_key(const char *topic) {
        if (NULL == topic) {
            return NULL;
        }

        static ldds_syncm<std::string,int> keys;
        auto k = keys.key(topic);

        if (k) {
            return k->data();
        }

        keys[topic];
        return get_key(topic);
    }
};
