#pragma once

#include <cstdbool>
#include <cstdint>
#include <cstdio>
#include <unordered_map>
#include <sstream>
#include <mutex>
#include "ldds_mutex.h"

template <typename K, typename V>
class ldds_syncm {
private:
    std::unordered_map<K,V>  _table;
    ldds_mutex _mutex;

public:
    ldds_syncm(void) {
        // printf("%s, %p\n", __func__, this);
    }

    ~ldds_syncm(void) {
        clear();
    }

    size_t size(void) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        return _table.size();
    }

    bool empty(void) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        return _table.empty();
    }

    /**
     * @brief 获取关键字在表中的指针
     */
    K* key(const K &k) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        auto i = _table.find(k);

        if (_table.end() == i) {
            return NULL;
        }

        return (K*)&i->first;
    }

    /**
     * @brief 设置元素
     */
    bool set(const K &k, const V &v) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        _table[k] = v;
        return true;
    }

    /**
     * @brief 引用元素
     * @param k键
     */
    V& operator[](const K &k) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        auto &v = _table[k];
        return v;
    }

    /**
     * @brief 获取元素
     */
    const V* find(const K &k) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        auto i = _table.find(k);
        if (_table.end() == i) {
            return NULL;
        }

        return &i->second;
    }

    std::pair<K,V> pair(void) {
        return std::pair<K,V>();
    }

    /**
     * @brief 获取元素
     */
    bool pop(std::pair<K,V> &p) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        auto i = _table.begin();
        if (_table.end() == i) {
            return false;
        }

        p.first = i->first;
        p.second = i->second;
        _table.erase(i->first);
        return true;
    }

    /**
     * @brief 删除元素
     */
    bool erase(const K &k) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        _table.erase(k);
        return true;
    }

    /**
     * @brief 清空表格
     */
    void clear(void) {
        std::lock_guard<ldds_mutex> lock(_mutex);

        _table.clear();
    }

    /**
     * @brief 遍历表格
     */
    template<typename F>
    void foreach(F f) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        for (auto &i : _table) {
            f((K&)i.first, (V&)i.second);
        }
    }

    /**
     * @brief 打印表格内容详情
     */
    void show(std::ostringstream &oss, int level=0, int step=4) const {
        std::lock_guard<ldds_mutex> lock(*(ldds_mutex*)&_mutex);

        std::string indent(level*step, ' ');
        std::string subint ((level+1)*step, ' ');

        oss << indent << "ldds_syncm[" << _table.size() << "]:{" << std::endl;
        for (auto &i : _table) {
            oss << subint << "[" << i.first << ", " << (void*)i.second << "]" << std::endl;
        }
        oss <<  indent << "}" << std::endl;
    }
};
