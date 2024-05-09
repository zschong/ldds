#pragma once

#ifdef __linux__
#include "port/linux/ldds_linux_mutex.h"
typedef ldds_linux_mutex ldds_mutex;
#else
#include "port/freertos/ldds_frtos_mutex.h"
typedef ldds_frtos_mutex ldds_mutex;
#endif
