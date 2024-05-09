#include <stdio.h>
#include "ldds_duration.h"

int main(void) {
    ldds_duration d;

    for (int i = 0; i < (1 << 20); i++) {
        d.stop();
    }

    printf("for[1M].duration:%.20f\n", d.f64());

    return 0;
}
