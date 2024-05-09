#include <list>
#include <stdio.h>
#include "ldds_payload.h"

int main(int argc, char **argv) {
    int count = (argc < 2) ? 10 : atoi(argv[1]);
    std::list<ldds_payload> plist;
    ldds_payload d1;

    d1.fill(0xaa, 10);
    for (int i = 0; i < count; i++) {
        plist.push_back(d1);
    }

    for (auto i : plist) {
        i.print(printf);
    }

    double a = 3.141592;
    double b = 2.141592;
    d1.format("test string %.19f", a/b);
    d1.print(printf);

    d1.format("read");
    d1.print(printf);

    return 0;
}
