#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Check if there is a default(none) clause visible at the compute construct
    if (acc_get_default_clause() == ACC_DEFAULT_NONE) {
        // Check if the variable appears in a data clause visible at the compute construct
        if (acc_get_data_clause() == ACC_DATA_NONE) {
            // Check if the variable appears in a reduction clause on the compute construct
            if (acc_get_reduction_clause() == ACC_REDUCTION_NONE) {
                // Check if the variable appears in a firstprivate, private, or reduction clause on the compute construct
                if (acc_get_firstprivate_clause() == ACC_FIRSTPRIVATE_NONE &&
                    acc_get_private_clause() == ACC_PRIVATE_NONE &&
                    acc_get_reduction_clause() == ACC_REDUCTION_NONE) {
                    // The variable is not private to a scope lexically enc losed within the compute construct
                    // and does not appear in a data clause, reduction clause, or firstprivate, private, or reduction clause
                    // on the compute construct, so it is treated as if it appears in a copy clause
                    err = 1;
                }
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