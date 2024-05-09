#pragma once

#include <cstdbool>
#include <cstdint>
#include <sstream>
#include <thread>
#include <mutex>
#include <list>
#include "ldds_mutex.h"

// typedef std::mutex ldds_mutex;

template <typename V>
class ldds_syncq {
private:
    std::list<V>  _queue;
    ldds_mutex     _mutex;
public:
    ldds_syncq(void) {
        // printf("%s, %p\n", __func__, this);
    }

    ~ldds_syncq(void) {
        clear();
    }

    bool empty(void) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        return _queue.empty();
    }

    uint32_t size(void) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        return _queue.size();
    }

    bool trypush(V &v, uint64_t timeout_ms) {
        if (_mutex.trylock(timeout_ms)) {
            _queue.push_back(v);
            _mutex.unlock();
            return true;
        }

        return false;
    }

    bool push(V &v) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        _queue.push_back(v);
        return true;
    }

    bool pop(V &out) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        if (_queue.empty()) {
            return false;
        }

        out = _queue.front();
        _queue.pop_front();
        return true;
    }

    void clear(void) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        _queue.clear();
    }

    template<typename F>
    void foreach(F f) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        for (auto v : _queue) {
            f(v);
        }
    }

    void show(std::ostringstream &oss, int level=0, int step=4) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);
        std::string indent(level*step, ' ');

        oss << indent << "ldds_syncq[" << _queue.size() << "]:{" << std::endl;
        for (auto i : _queue) {
            oss << indent << "    " << i << "," << std::endl;
        }
        oss << indent << "}" << std::endl;
    }
};
