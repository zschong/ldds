#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "ldds_duration.h"
#include "ldds_syncq.h"

void on_item(const int& v) {
    printf("%s v=%d\n", __func__, v);
}

void push_thread(void* arg) {
    ldds_syncq<int> *q = (ldds_syncq<int>*)arg;
    printf("thread:%x\n", gettid());

    for (int i = 0; i < 100000; i++) {
        q->push(i);
        if (i%1000==0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void test_queue(int max) {
    ldds_syncq<int> q;

    for (int i = 0; i < max; i++) {
        auto p = new std::thread(push_thread, &q);
        p->detach();
    }
    while(1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        printf("test_queue.size=%d\n", q.size());
    }
}

int main(int argc, char **argv) {
    int times = (argc > 1) ? atoi(argv[1]) : (1 << 20);
    ldds_syncq<int> q;
    ldds_duration t;
    test_queue(15);
    std::this_thread::sleep_for(std::chrono::minutes(10));
    return 0;

    for (int i = 0; i < times; i++) {
        q.push(i);
    }

    t.stop();
    printf("timediff:%f, time=%d\n", t.f64(), times);

    q.foreach(on_item);
}
