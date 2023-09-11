#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

int main() {
    int err = 0;
    int x = 0;
    int y = 0;

    // Initialize the data
    x = rand() % 100;
    y = rand() % 100;

    // Create a parallel region with firstprivate clause
    #pragma acc parallel firstprivate(x, y)
    {
        // Do some work
        x = x + y;
        y = y + x;
    }

    // Check the results
    if (x != y) {
        err = 1;
    }

    return err;
}