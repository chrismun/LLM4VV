#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    acc_init(acc_device_host);

    // Create a structured data region
    acc_structured_data_region_t region;
    region.type = acc_structured_data_region_type_t::acc_structured_data_region_type_shared;
    region.size = 1024;
    region.alignment = 16;
    region.data = (void*)malloc(region.size);

    // Create a compute region
    acc_compute_region_t compute_region;
    compute_region.type = acc_compute_region_type_t::acc_compute_region_type_kernel;
    compute_region.size = 1024;
    compute_region.alignment = 16;
    compute_region.data = (void*)malloc(compute_region.size);

    // Create a no_create clause
    acc_no_create_clause_t no_create_clause;
    no_create_clause.type = acc_no_create_clause_type_t::acc_no_create_clause_type_structured;
    no_create_clause.size = 1024;
    no_create_clause.alignment = 16;
    no_create_clause.data = (void*)malloc(no_create_clause.size);

    // Attach the no_create clause to the compute region
    acc_attach_no_create_clause(compute_region, no_create_clause);

    // Run the kernel
    acc_run_kernel(compute_region, (void*)&test1_kernel, 1, 1, 1);

    // Detach the no_create clause from the compute region
    acc_detach_no_create_clause(compute_region, no_create_clause);

    // Free the memory
    free(region.data);
    free(compute_region.data);
    free(no_create_clause.data);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}