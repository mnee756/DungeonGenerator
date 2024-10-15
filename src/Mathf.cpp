#include "Mathf.h"

int getRandom(int a, int b)
{
    return a + std::rand() % (b - a + 1);
}

double getRandom(double a, double b)
{
    double random = static_cast<double>(std::rand()) / RAND_MAX;  // Random double between 0 and 1
    return a + random * (b - a);  // Scale it to the range [a, b]
}