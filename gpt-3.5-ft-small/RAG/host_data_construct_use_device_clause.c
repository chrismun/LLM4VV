int* virtual_a = (int *)malloc(VIRTUAL_LENGTH * sizeof(int));
    int* a = (int *)malloc(VIRTUAL_LENGTH * sizeof(int));
    int sum = 0;
}

int test(){
    int computed_sum = 0;
    int boolean_failed = 0;
    for (int x = 0; x < VIRTUAL_LENGTH; ++x){
        virtual_a[x] = x;
        computed_sum += x;
    }
    #pragma acc parallel present(virtual_a[0:VIRTUAL_LENGTH]) present(computed_sum)
    {
        #pragma acc loop
        for (int x = 0; x < VIRTUAL_LENGTH; ++x){
            computed_sum -= virtual_a[x];
        }
        #pragma acc atomic seq
        atomic_add_int(&computed_sum, computed_sum);
    }
    return computed_sum;
}

rincipal int main(){
    int failcode;
    int failed;
    failed = 0;
    #pragma acc data present(a[0:VIRTUAL_LENGTH])
    {
        #pragma acc update device(a[0:VIRTUAL_LENGTH])
    }
    if (test() != a[VIRTUAL_LENGTH - 1] * (a[VIRTUAL_LENGTH - 1] + 1) / 2){
        failed = 1;
    }
    #pragma acc host_data use_device(a[0:VIRTUAL_LENGTH])
    {
        for (int x = 0; x < VIRTUAL_LENGTH; ++x){
            a[x] = 0;
        }
    }
    if (failed == 0){
        failcode = 0;
    }
    else{
        failcode = 1;
    }
    return failcode;
}