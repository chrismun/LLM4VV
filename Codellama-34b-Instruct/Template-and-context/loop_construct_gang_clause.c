#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Check if the parent compute construct is a parallel construct or an orphaned loop construct
    if (acc_get_parent_construct_type() == ACC_PARALLEL ||
        acc_get_parent_construct_type() == ACC_LOOP) {
        // Check if the gang clause is present
        if (acc_get_gang_clause() != NULL) {
            // Check if the associated dimension is valid
            if (acc_get_gang_dimension() != 1 && acc_get_gang_dimension() != 2 &&
                acc_get_gang_dimension() != 3) {
                err = 1;
            }
            // Check if the number of gangs is valid
            if (acc_get_num_gangs() != 0 && acc_get_num_gangs() != 1 &&
                acc_get_num_gangs() != 2 && acc_get_num_gangs() != 3) {
                err = 1;
            }
        }
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