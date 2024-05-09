#include <cstdlib>
#include <cstdio>
#include "ldds_msg.h"

int main(int argc, char **argv) {
    ldds_msg_t m1 = ldds_msg_create("toipc.xx", (void*)"test", 5);

    ldds_msg_print(m1, printf);
    ldds_msg_valid(m1);

    ldds_msg_t m2 = ldds_msg_dup(m1);

    ldds_msg_print(m2, printf);
    ldds_msg_valid(m2);

    ldds_msg_free(m1);
    ldds_msg_free(m2);
}
