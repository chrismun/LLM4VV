#include <stdio.h>
#include <openacc.h>

int main() {
    int isPresent = 0;

    // Check if OpenACC is present
    #ifdef _OPENACC
        isPresent = 1;
    #endif

    if (isPresent) {
        printf("OpenACC is supported\n");
    } else {
        printf("OpenACC is not supported\n");
    }

    return 0;
}