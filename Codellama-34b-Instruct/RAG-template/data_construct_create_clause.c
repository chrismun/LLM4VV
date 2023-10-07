#include "acc_testsuite.h"

#ifndef T1
//T1:data construct create clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a new data construct
    acc_data_construct_t data_construct;
    acc_data_construct_init(&data_construct, NULL, 0, 0);

    // create a new variable
    int var = 0;

    // add the variable to the data construct
    acc_data_construct_add_variable(&data_construct, &var, 0, 0);

    // create a new compute construct
    acc_compute_construct_t compute_construct;
    acc_compute_construct_init(&compute_construct, NULL, 0, 0);

    // add the data construct to the compute construct
    acc_compute_construct_add_data_construct(&compute_construct, &data_construct, 0, 0);

    // create a new enterdata directive
    acc_enterdata_directive_t enterdata_directive;
    acc_enterdata_directive_init(&enterdata_directive, NULL, 0, 0);

    // add the compute construct to the enterdata directive
    acc_enterdata_directive_add_compute_construct(&enterdata_directive, &compute_construct, 0, 0);

    // create a new create clause
    acc_create_clause_t create_clause;
    acc_create_clause_init(&create_clause, NULL, 0, 0);

    // add the create clause to the enterdata directive
    acc_enterdata_directive_add_create_clause(&enterdata_directive, &create_clause, 0, 0);

    // execute the enterdata directive
    acc_enterdata_directive_execute(&enterdata_directive);

    // check that the variable was created and attached to the data construct
    if (acc_data_construct_get_variable(&data_construct, 0) != &var) {
        err = 1;
    }

    // check that the data construct was created and attached to the compute construct
    if (acc_compute_construct_get_data_construct(&compute_construct, 0) != &data_construct) {
        err = 1;
    }

    // check that the create clause was executed
    if (acc_create_clause_get_executed(&create_clause) != 1) {
        err = 1;
    }

    // clean up
    acc_data_construct_destroy(&data_construct);
    acc_compute_construct_destroy(&compute_construct);
    acc_enterdata_directive_destroy(&enterdata_directive);
    acc_create_clause_destroy(&create_clause);

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