#pragma once

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include "ldds_hex.h"

class ldds_payload {
private:
    void    *_data;
    uint32_t _size;
    uint32_t _length;

public:
    ldds_payload(void) : _data(NULL), _size(0), _length(0) {}

    ldds_payload(const ldds_payload &p) : _data(NULL), _size(0), _length(0)  {
        if (NULL == p._data) {
            return;
        }

        _data = malloc(p._size);

        if (_data) {
            memcpy(_data, p._data, p._length);
            _length = p._length;
            _size   = p._size;
        }
    }

    ~ldds_payload(void) {
        // printf("%s\n", __func__);
        if (_data) {
            free(_data);
        }
    }

    void* data(void) const {
        return (void*)_data;
    }

    bool empty(void) const {
        return _length < 1;
    }

    uint32_t size(void) const {
        return _size;
    }

    uint32_t length(void) const {
        return _length;
    }

    bool resize(uint32_t len) {
        if (_data) {
            free(_data);
        }

        _data = malloc(len);

        if (NULL == _data) {
            _length = 0;
            _size = 0;
            return false;
        }

        _size = len;
        _length = 0;

        return true;
    }

    bool set_data(const void *data, uint32_t len) {
        if (NULL == data || len < 1) {
            return false;
        }

        if (len <= _size) {
            memcpy(_data, data, len);
            _length = len;
            return true;
        }

        if (resize(len)) {
            return set_data(data, len);
        }

        return false;
    }

    bool set_string(const std::string &s) {
        return set_data(s.data(), s.length());
    }

    void fill(uint8_t c, uint32_t len) {
        if (len <= _size) {
            memset(_data, c, len);
            _length = len;
        }

        if (resize(len)) {
            memset(_data, c, len);
            _length = len;
        }
    }

    int format(const char *fmt, ...) {
        if (NULL == fmt) {
            return 0;
        }

        std::string tmp;
        va_list ap;

        tmp.resize(4096);
        va_start(ap, fmt);
        int ret = vsnprintf((char*)tmp.data(), tmp.size(), fmt, ap);
        va_end(ap);

        if (ret > 0) {
            set_data(tmp.data(), ret);
        } else {
            _length = 0;
        }

        return _length;
    }

    void show(std::ostringstream &oss) const {
        ldds_hex hex(_data, _length);

        oss << "ldds_payload: {\n"
            << "    .hex        = [" << hex.length() << "]" << hex.data() << "\n"
            << "    .size       = " << _size         << "\n"
            << "    .length     = " << _length       << "\n"
            << "    .data       = " << (char*)_data  << "\n"
            << "}\n";
    }
};
