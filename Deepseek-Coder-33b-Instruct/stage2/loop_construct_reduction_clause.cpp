#include <iostream>
#include <cstdlib>
#include <ctime>

#define I 100

int main() {
    srand(time(0));
    int x = 0;
    int y = 0;

    #pragma acc parallel copy(x) reduction(+:y)
    {
        int z = 0;
        #pragma acc loop gang vector reduction(+:x,z)
        for (int i = 0; i < I; ++i) {
            x += 1;
            z += 2;
        }
        y += z;
    }

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    return 0;
}