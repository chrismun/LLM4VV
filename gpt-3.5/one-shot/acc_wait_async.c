#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define N 1000000
#define NUM_TEST_CALLS 10

void init_array(float *a, float *b, int size) {
    for (int i = 0; i < size; ++i) {
        a[i] = i + 1;
        b[i] = 0;
    }
}

int validate_result(float *a, float *b, int size) {
    for (int i = 0; i < size; ++i) {
        if (fabs(b[i] - (a[i] * a[i])) > 1e-5) {
            return 0;