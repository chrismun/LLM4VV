#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    int multiplicand[10][10] = {
        { 718, 557, 428, 351, 303, 240, 226, 187, 196, 142 },
        { 716, 618, 518, 384, 317, 265, 210, 199, 168, 173 },
        { 810, 619, 606, 424, 356, 295, 289, 220, 191, 201 },
        { 834, 674, 493, 457, 373, 352, 317, 260, 249, 195 },
        { 858, 785, 565, 494, 421, 359, 286, 323, 225, 289 },
        { 877, 803, 669, 544, 504, 387, 346, 390, 320, 280 },
        { 1012, 841, 774, 606, 588, 417, 453, 454, 430, 343 },
        { 1001, 911, 826, 681, 593, 469, 485, 479, 410, 403 },
        { 1101, 1005, 901, 761, 746, 598, 564, 477, 485, 429 },
        { 1167, 1116, 957, 845, 787, 668, 610, 574, 565, 529 }
    };
    int a = 0;

    #pragma acc data copy(multiplicand[0:10][0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2)
            for (int i = 0; i < 10; ++i){
                for (int j = 0; j < 10; ++j){
                    a = a + multiplicand[i][j];
                }
            }
        }
    }

    real_t false_margin = PRECISION;

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < 10; ++y){
            a = a - multiplicand[x][y];
        }
    }
    if (fabs(a) > 80 * 10 * false_margin){
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}