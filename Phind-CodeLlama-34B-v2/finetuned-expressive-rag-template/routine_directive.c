#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#pragma acc routine seq
int add(int a, int b) {
    return a + b;
}

int main() {
    int a = 5;
    int b = 10;
    int result = 0;

    #pragma acc parallel
    {
        result = add(a, b);
    }

    if (result == 15) {
        printf("Routine directive is working properly.\n");
        return 0;
    } else {
        printf("Routine directive is not working properly.\n");
        return 1;
    }
}