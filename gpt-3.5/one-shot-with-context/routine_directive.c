#include <stdio.h>
#include <stdlib.h>

// Function declaration with routine directive
#pragma acc routine seq nohost
int square(int num) {
    return num * num;
}

int main() {
    int num = 5;

    // Call the square function
    int result = square(num);

    printf("Result: %d\n", result);

    return 0;
}