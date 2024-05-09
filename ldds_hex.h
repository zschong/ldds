#pragma once

#include <string>

class ldds_hex {
private:
    std::string _buf;

public:
    ldds_hex(const char *s) {
        write(std::string(s));
    }

    ldds_hex(const void *data, uint32_t len) {
        write(data, len);
    }

    template<typename T>
    ldds_hex(const T &s) {
        write(s.data(), s.length());
    }

    uint8_t* data(void) const {
        return (uint8_t*)_buf.data();
    }

    uint32_t length(void) const {
        return _buf.length();
    }

    uint32_t size(void) const {
        return _buf.size();
    }

    int write(const void *data, uint32_t len) {
        if (NULL == data || len < 1 || data == _buf.data()) {
            return 0;
        }

        _buf.resize(len * 3 + 3, 0);

        static const char *hex = "0123456789ABCDEF";
        const uint8_t *u = (uint8_t*)data;


        char *p = (char*)_buf.data();

        *p++ = '[';
        for (int i = 0; i < len; i++) {
            *p++ = hex[ (u[i] >> 4) ];
            *p++ = hex[ (u[i] & 0xf) ];
            *p++ = ' ';
        }

        if (' ' == p[-1]) {
            p[-1] = ']';
            *p = 0;
        } else {
            *p = 0;
        }

        return _buf.size();
    }

    template<typename T>
    int write(const T &value) {
        return write((void*)value.data(), value.length());
    }
};
