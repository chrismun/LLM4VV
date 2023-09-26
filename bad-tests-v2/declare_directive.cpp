#include <iostream>
#include <cstdlib>
#include <cmath>

#pragma acc declare copy(x)

int main() {
    int x = 10;
    #pragma acc parallel
    {
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            x = x + i;
        }
    }
    std::cout << "x = " << x << std::endl;
    return 0;
}