#pragma once

#include <typeinfo>
#include <string>

template<typename T>
class ldds_rtti {
public:
    static const char* name(void) {
        static const char *p = typeid(T).name();
        return p;
    }

    static uint32_t key(const char *str) {
        uint32_t value = 2166136261U;

        if (NULL == str) {
            return 0;
        }

        while (*str) {
            value ^= *str++;
            value *= 16777619U;
        }

        return value;
    }

    static uint32_t id(void) {
        static uint32_t value = -1;

        if (-1 == value) {
            value = key(name());
        }

        return value;
    }
};
