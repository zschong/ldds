#include <cstdio>
#include <cstdlib>
#include <string>
#include "ldds_duration.h"
#include "ldds_syncm.h"

void on_item(const std::string& key, const std::string &value, void *p) {
    printf("%s [%s]=%s, p=%p\n", __func__, key.data(), value.data(), p);
}

double hdiff(int times) {
    ldds_syncm<std::string, std::string> m;
    ldds_duration t;

    t.start();
    for (int i = 0; i < times; i++) {
        char k[32];
        char v[32];

        snprintf(k, sizeof(k), "k%030d", i);
        snprintf(v, sizeof(v), "v%030d", i);
        m[k] = v;
    }

    t.stop();
    printf("map.size=%d, h.diff=%10f\n", times, t.f64());

    t.start();
    auto p = m.pair();
    while (m.pop(p)) {
        on_item(p.first, p.second, &p);
    }
    t.stop();
    printf("map.size=%d, h.diff=%10f\n", times, t.f64());

    return t.f64();
}

int main(int argc, char **argv) {
    int times = (argc > 1) ? atoi(argv[1]) : (1 << 14);
    double h = hdiff(times);

    printf("map.size=%d, h.diff=%10f\n", times, h);

    return 0;
}
