```c
#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct reduction clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int a[100];
    int b[100];
    int sum = 0;
    int product = 1;
    int max = INT_MIN;
    int min = INT_MAX;
    int bitwise_and = ~0;
    int bitwise_or = 0;
    int bitwise_xor = 0;
    int logical_and = 1;
    int logical_or = 0;
    int logical_eqv = 1;
    int logical_neqv = 0;

    for (int x = 0; x < 100; ++x) {
        a[x] = rand() % 100;
        b[x] = rand() % 100;
    }

    #pragma acc serial
    {
        #pragma acc loop reduction(+:sum)
        for (int x = 0; x < 100; ++x) {
            sum += a[x] + b[x];
        }

        #pragma acc loop reduction(*:product)
        for (int x = 0; x < 100; ++x) {
            product *= a[x] * b[x];
        }

        #pragma acc loop reduction(max:max)
        for (int x = 0; x < 100; ++x) {
            max = max > a[x] ? max : a[x];
        }

        #pragma acc loop reduction(min:min)
        for (int x = 0; x < 100; ++x) {
            min = min < a[x] ? min : a[x];
        }

        #pragma acc loop reduction(&:bitwise_and)
        for (int x = 0; x < 100; ++x) {
            bitwise_and &= a[x];
        }

        #pragma acc loop reduction(|:bitwise_or)
        for (int x = 0; x < 100; ++x) {
            bitwise_or |= a[x];
        }

        #pragma acc loop reduction(^:bitwise_xor)
        for (int x = 0; x < 100; ++x) {
            bitwise_xor ^= a[x];
        }

        #pragma acc loop reduction(.and.:logical_and)
        for (int x = 0; x < 100; ++x) {
            logical_and = logical_and && (a[x] != 0);
        }

        #pragma acc loop reduction(.or.:logical_or)
        for (int x = 0; x < 100; ++x) {
            logical_or = logical_or || (a[x] != 0);
        }

        #pragma acc loop reduction(.eqv.:logical_eqv)
        for (int x = 0; x < 100; ++x) {
            logical_eqv = logical_eqv == (a[x] != 0);
        }

        #pragma acc loop reduction(.neqv.:logical_neqv)
        for (int x = 0; x < 100; ++x) {
            logical_neqv = logical_neqv != (a[x] != 0);
        }
    }

    int host_sum = 0;
    int host_product = 1;
    int host_max = INT_MIN;
    int host_min = INT_MAX;
    int host_bitwise_and = ~0;
    int host_bitwise_or = 0;
    int host_bitwise_xor = 0;
    int host_logical_and = 1;
    int host_logical_or = 0;
    int host_logical_eqv = 1;
    int host_logical_neqv = 0;

    for (int x = 0; x < 100; ++x) {