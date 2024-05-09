#include <cstdio>
#include "ldds_time.h"

int main(void) {
    ldds_time t;

    t.boottime();
    printf("boottime:%20ld, %f\n", t.unixnano_u64(), t.unixnano_f64());

    t.realtime();
    printf("realtime:%20ld, %f\n", t.unixnano_u64(), t.unixnano_f64());

    t.monotonic();
    printf("monotonic:%19ld, %f\n", t.unixnano_u64(), t.unixnano_f64());

    return 0;
}
