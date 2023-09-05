#include <stdio.h>
#include <openacc.h>

int main() {
    int data = 123;
    int isPresent;

    isPresent = acc_is_present(&data, sizeof(int));

    printf("Is data present on device? %d\n", isPresent);

    return 0;
}