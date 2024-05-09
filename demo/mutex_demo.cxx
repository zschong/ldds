#include <thread>
#include <chrono>
#include <iostream>
#include "ldds_mutex.h"

void test_thread(ldds_mutex &mutex) {
    while (1) {
        {
            std::lock_guard<ldds_mutex> lock(mutex);
            std::cout << "thread:" << std::hex << std::this_thread::get_id() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(void) {
    ldds_mutex mutex;

    for (int i = 0; i < 10; i++) {
        std::thread(test_thread, std::ref(mutex)).detach();
    }

    std::this_thread::sleep_for(std::chrono::seconds(100));
    return 0;
}
