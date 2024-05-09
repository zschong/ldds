#pragma once

#include <stdio.h>
#include <sstream>
#include <string>
#include "ldds_syncq.h"
#include "ldds_syncm.h"
#include "ldds_msgcc.h"
#include "ldds_msg.h"

class ldds_node {
private:
    ldds_syncm<const char*, ldds_msg_handler_t> _handler_table;
    ldds_syncq<ldds_msg_t> _msg_queue;

private:
    void _handle_msg(const ldds_msgcc &m) {
        auto h = _handler_table.find(m.topic());

        if (h && *h) {
            (*h)((ldds_msg_t)&m);
        }
    }

public:
    ldds_node(void) {
        // printf("%s, %p\n", __func__, this);
    }

    ~ldds_node(void) {
        clear();
    }

    bool pub(ldds_msg_t m) {
        if (m) {
            return _msg_queue.push(m);
        }

        return false;
    }

    bool sub(const char *topic, ldds_msg_handler_t handler) {
        auto key = ldds_msgcc::get_key(topic);

        if (NULL == key) {
            return false;
        }

        _handler_table[key] = handler;
        return true;
    }

    bool unsub(const char *topic, ldds_msg_handler_t handler) {
        auto key = ldds_msgcc::get_key(topic);

        if (NULL == key) {
            return false;
        }
        
        return _handler_table.erase(key);
    }

    void clear(void) {
        _msg_queue.foreach([](ldds_msg_t m) {
            if (m) {
                ldds_msg_free(m);
            }
        });
    }

    int dispatch(void) {
        int msg_count = 0;

        for(ldds_msg_t m = NULL; _msg_queue.pop(m); m = NULL) {
            _handle_msg(*(ldds_msgcc*)m);
            ldds_msg_free(m);
            msg_count++;
        }

        return msg_count;
    }

    void show(std::ostringstream &oss, int level=0, int step=4) const {
        std::string indent(level*step, ' ');
        std::string subind((level+1)*step, ' ');

        oss << indent << "ldds_node(" << this << "):{" << std::endl
            << subind << "msg_queue:" << std::endl;
        _msg_queue.show(oss, level+1, step);
        oss << subind << "handlers:" << std::endl;
        _handler_table.show(oss, level+1, step);
        oss << indent << "}" << std::endl;
    }
};
