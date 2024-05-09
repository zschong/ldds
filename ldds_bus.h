#pragma once

#include <sstream>
#include "ldds_syncm.h"
#include "ldds_node.h"

class ldds_bus {
private:
    ldds_syncm<ldds_node*, uint32_t> _nodes;
    std::string _name;

public:
    ldds_bus(void) {
        // printf("%s, %p\n", __func__, this);
    }

    bool empty(void) const {
        return _nodes.empty();
    }

    bool sub(ldds_node *node) {
        if (NULL == node) {
            return false;
        }

        _nodes[node];

        return true;
    }

    bool unsub(ldds_node *node) {
        if (NULL == node) {
            return false;
        }

        _nodes.erase(node);

        return true;
    }

    bool pub(ldds_msg_t msg) {
        if (NULL == msg) {
            return false;
        }

        size_t size = _nodes.size();

        _nodes.foreach([&size, msg](ldds_node *const &node, const uint32_t &value) {
            if (--size) {
                node->pub(ldds_msg_dup(msg));
            } else {
                node->pub(msg);
            }

            ((uint32_t&)value)++;
        });

        return true;
    }

    void set_name(const std::string &name) {
        _name = name;
    }

    void show(std::ostringstream &oss, int level=0, int step=4) const {
        std::string indent(level*step, ' ');
        std::string subind((level+1)*step, ' ');

        oss << indent << "ldds_bus: {" << std::endl
            << subind << "name: " << _name << std::endl
            << subind << "size: " << _nodes.size() << std::endl;
        _nodes.foreach([&oss,level,step](ldds_node *node, uint32_t &value) {
            node->show(oss, level+1, step);
        });
        oss << indent << "}" << std::endl;
    }
};
