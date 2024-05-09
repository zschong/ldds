#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "ldds_node.h"

void msg_handler(ldds_msg_t m) {
    ldds_msg_print(m, printf);
}

template<typename T>
void show(T &t) {
    std::ostringstream oss;
    t.show(oss);
    std::cout << oss.str() << std::endl;
}

int main(int argc, char **argv) {
    int times = (argc > 1) ? atoi(argv[1]) : (1 << 3);
    ldds_node node;

    for (int i = 0; i < times; i++) {
        char buf[32];
        snprintf(buf, sizeof(buf), "topic.%03d", i);
        ldds_msg_t m = ldds_msg_create(buf, buf, strlen(buf));
        ldds_msg_fill(m, 'd', 64);
        node.sub(buf, msg_handler);
        node.pub(m);
        //ldds_msg_print(m, printf);
    }

	show(node);

    //node.foreach();

    return 0;
}
