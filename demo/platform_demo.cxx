#include <unistd.h>
#include <iostream>
#include <sstream>
#include <thread>
#include "ldds_platform.h"

std::thread msg_thread(ldds_node &mq) {
    while (true) {
        //mq.foreach();
        usleep(10000);
    }
}

void handler1(ldds_msg_t msg) {
    printf("%s\n", __func__);
    ldds_msg_print(msg, printf);
}

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

template<typename T>
void show(T &t) {
    std::ostringstream oss;
    t.show(oss);
    std::cout << oss.str() << std::endl;
}

int main(void) {
    ldds_platform platform;
    ldds_node node[32];

    for (int i = 0; i < ARRAY_SIZE(node); i++) {
        char topic[32];
        snprintf(topic, sizeof(topic), "topic.%03d", i%3);
        platform.sub(topic, &node[i], handler1);

        std::thread(msg_thread, std::ref(node[i])).detach();
    }
    show(platform);

    for (int i = 3; i < ARRAY_SIZE(node); i++) {
        char topic[32];
        snprintf(topic, sizeof(topic), "topic.%03d", i%3);
        //platform.unsub(topic, &node[i], handler1);
    }


    while (char c = getchar()) {
        char topic[32];
        char payload[32];
        snprintf(topic, sizeof(topic), "topic.%03d", c%3);
        snprintf(payload, sizeof(payload), "payload %03d", c);
        ldds_msg_t msg = ldds_msg_create(topic, payload, strlen(payload));
        platform.pub(msg);

        show(platform);
    }

    return 0;
}
