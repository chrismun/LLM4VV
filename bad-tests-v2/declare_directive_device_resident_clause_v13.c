#include "openacc.h"
#include <stdlib.h>
#include <math.h>

#define ERROR_TOLERANCE 1.0e-6
#define ARRAY_SIZE 1024

float a[ARRAY_SIZE], b[ARRAY_SIZE], result[ARRAY_SIZE];

__declspec(target(mic)) float a[ARRAY_SIZE], b[ARRAY_SIZE], result[ARRAY_SIZE];

// Initialize arrays on the host
for (int i=0; i<ARRAY_SIZE; i++) {
    a[i] = (float)i;
    b[i] = (float)i;
}

// Declare the arrays as device resident
#pragma acc declare device_resident(a, b, result)

// Launch kernel on the device
#pragma acc parallel loop
for (int i=0; i<ARRAY_SIZE; i++) {
    result[i] = a[i] + b[i];
}

// Validate the result
bool success = true;
for (int i=0; i<ARRAY_SIZE; i++) {
    if (fabs(result[i] - (a[i]+b[i]) > ERROR_TOLERANCE) {
        success = false;
        break;
    }
}

if(success)
    printf("Test Passed\n");
else
    printf("Test Failed\n");

return 0;