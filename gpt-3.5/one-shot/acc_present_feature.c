#include <stdio.h>
#include <unistd.h>
#include <openacc.h>

int main() {
    int is_present = 0;
    #ifdef _OPENACC
    is_present = 1;
    #endif

    printf("OpenACC support is %s\n", is_present ? "present" : "not present");

    return 0;
}