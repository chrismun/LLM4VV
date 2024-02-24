#include <iostream>
#include <stdlib.h>

#pragma acc declare copy(a)
int a;

int main() {
    a = 5;

    #pragma acc parallel copy(a)
    {
        a = a * 2;
    }

    std::cout << "Value of a: " << a << std::endl;

    return 0;
}