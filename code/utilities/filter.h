#ifndef FILTER_H
#define FILTER_H

#include "memory_management.h"

namespace util {

void filter (float *data,
             int    fill,
             int    N,
             MEMORY mem_buffer);

}

#endif
