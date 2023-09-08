#include "acc_testsuite.h"
#pragma acc routine(no_set_val)
real_t set_val = 1;
int no_set_val(int *a, real_t *data){
    if (data[0] == set_val){
        return 1;
    }
    else {
        return 0;