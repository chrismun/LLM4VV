#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

int main() {
    int failcode = 0;

    // Check if the OpenACC runtime is present
    if (!acc_is_present()) {
        printf("OpenACC runtime is not present\n");
        failcode = 1;
    }

    // Check if the OpenACC compiler is present
    if (!acc_is_compiler_present()) {
        printf("OpenACC compiler is not present\n");
        failcode = 1;
    }

    // Check if the OpenACC specification is supported
    if (!acc_is_specification_supported(ACC_SPEC_VERSION)) {
        printf("OpenACC specification is not supported\n");
        failcode = 1;
    }

    return failcode;
}