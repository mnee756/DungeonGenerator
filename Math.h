#pragma once
#include <cstdlib>
#include <iostream>

int getRandom(int a, int b) {
    return a + std::rand() % (b - a + 1);
}