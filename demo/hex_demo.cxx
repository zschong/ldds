#include <iostream>
#include "ldds_hex.h"

int main(void) {
    ldds_hex hex("test");

    std::cout << hex.data() << std::endl;

    return 0;
}
