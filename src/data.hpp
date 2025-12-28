#pragma once
#include <cstddef>

struct data{
    size_t size;
    unsigned char *text;
    data(size_t s, unsigned char *t) {
        size = s;
        text = t;
    }
};