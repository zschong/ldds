#include <iostream>
#include <sstream>
#include "ldds_bus.h"

void handler1(ldds_msg_t msg) {
    printf("%s\n", __func__);
    ldds_msg_print(msg, printf);
}

void handler2(ldds_msg_t msg) {
    printf("%s\n", __func__);
    ldds_msg_print(msg, printf);
}

int main(void) {
    ldds_bus bus;
    ldds_node node1;
    ldds_node node2;
    ldds_node node3;

    const char *topic1 = "topic.1";
    const char *topic2 = "topic.2";
    const char *payload1 = "payload 1";
    const char *payload2 = "payload 2";

    node1.sub(topic1, handler1);
    node2.sub(topic1, handler2);
    node3.sub(topic2, handler2);

    bus.sub(&node1);
    bus.sub(&node2);
    bus.sub(&node3);

    ldds_msg_t msg1 = ldds_msg_create(topic1, payload1, strlen(payload1));
    ldds_msg_t msg2 = ldds_msg_create(topic2, payload2, strlen(payload2));

    bus.pub(msg1);
    bus.pub(msg2);

    std::ostringstream oss;
    bus.show(oss);
    std::cout << oss.str() << std::endl;
    getchar();

    node1.dispatch();
    node2.dispatch();
    node3.dispatch();
    
    return 0;
}
