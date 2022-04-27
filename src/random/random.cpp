#include <random>
#include <iostream>

int main() {
    std::mt19937 rng;
    std::uniform_int_distribution<uint32_t> dist(0,255);
    for(int i = 0; i < 20; i++) {
        std::cout << dist(rng) << ' ' << dist(rng) << ' ' << dist(rng) << '\n';
    }
}

