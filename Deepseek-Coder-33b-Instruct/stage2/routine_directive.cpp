#include <iostream>
#include <cstdlib>
#include <ctime>

#pragma acc routine seq
void vector_add(int* a, int* b, int* c, int n) {
    for(int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    const int n = 1000000;
    int a[n], b[n], c[n];

    srand(time(0));
    for(int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop
        for(int i = 0; i < n; i++) {
            vector_add(a, b, c, n);
        }
    }

    for(int i = 0; i < n; i++) {
        if(c[i] != a[i] + b[i]) {
            std::cout << "Error at index " << i << std::endl;
            return 1;
        }
    }

    std::cout << "Success" << std::endl;
    return 0;
}