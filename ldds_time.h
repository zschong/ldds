#pragma once

#ifdef __linux__
#include "port/linux/ldds_linux_time.h"
typedef ldds_linux_time ldds_time;
#else
#include "port/freertos/ldds_frtos_time.h"
typedef ldds_frtos_time ldds_time;
#endif
