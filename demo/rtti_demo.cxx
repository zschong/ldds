#include <stdio.h>
#include <unordered_map>
#include "ldds_duration.h"
#include "ldds_rtti.h"

template<typename T>
double bench_id(int times) {
    ldds_duration d;

    for (int i = 0; i < times; i++) {
        ldds_rtti<T>::id();
    }
    d.stop();

    return d.f64();
}

template<typename T>
double bench_key(int times) {
    ldds_duration d;

    for (int i = 0; i < times; i++) {
        ldds_rtti<T>::key(typeid(T).name());
    }
    d.stop();

    return d.f64();
}

template<typename T>
void bench_diff(int times) {
    double a = bench_key<T>(times);
    double b = bench_id<T>(times);

    printf("%20s: times=%-8d, [key=%.6f, id=%.6f]=%.6f\n", 
            typeid(T).name(), times, a, b, a/b);
}

namespace ipc {
    class message1{};
    class message2{};
};

int main(void) {
    int times = (1<<20);

    bench_diff<ipc::message1>(times);
    bench_diff<ipc::message2>(times);
    bench_diff<std::string>(times);
    //bench_diff<std::unordered_map>(times);

    return 0;
}
