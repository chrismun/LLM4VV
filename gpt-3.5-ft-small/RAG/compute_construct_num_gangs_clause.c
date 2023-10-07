#ifndef T1
//T1:parallel,construct-independent,V:2.0-3.0
int test1(){
    int err = 0;
    int clause_err = 0;
    int num_gangs = acc_get_num_gangs();
    int num_gangs_clause[3] = {33, 27, 30};

    real_t * a = (real_t *)malloc(num_gangs * loop * sizeof(real_t));
    real_t * b = (real_t *)malloc(num_gangs * loop * sizeof(real_t));

    for (int x = 0; x < num_gangs; ++x)
        for (int y = 0; y < loop; ++y){
            a[x * loop + y] = rand() / (real_t)(RAND_MAX / 10);
            b[x * loop + y] = 0;
        }

    #pragma acc data copyin(a[0:num_gangs*loop]) copy(b[0:num_gangs*loop])
    {
        for (int x = 0; x < num_gangs; ++x){
            for (int y = 0; y < loop; ++y){
                b[x * loop + y] = 0;
            }
        }

        #pragma acc parallel num_gangs(1, loop%10)
        {
            #pragma acc loop gang
            for (int x = 0; x < loop; ++x){
                b[x] = 1;
                for (int y = 0; y < num_gangs; ++y){
                    b[x] += a[x + y * loop];
                }
            }
        }
    }

    for (int x = 0; x < loop; ++x){
        clause_err = 0;
        for (int y = 0; y < num_gangs; ++y){
            clause_err += fabsb(b[x + y * loop] - (a[x + y * loop] + 1)) > PRECISION;
        }
        if (clause_err != 0) {
            err += clause_err;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:kernels,construct-independent,V:2.0-3.0
int test2(){
    int err = 0;
    int clause_err = 0;
    int num_gangs = acc_get_num_gangs();
    int loop_index;

    real_t * a = (real_t *)malloc(num_gangs * loop * sizeof(real_t));
    real_t * b = (real_t *)malloc(num_gangs * loop * sizeof(real_t));

    for (int x = 0; x < num_gangs; ++x)
        for (int y = 0; y < loop; ++y){
            a[x * loop + y] = rand() / (real_t)(RAND_MAX / 10);
            b[x * loop + y] = 0;
        }

    #pragma acc data copyin(a[0:num_gangs*loop]) copy(b[0:num_gangs*loop])
    {
        for (int x = 0; x < num_gangs; ++x){
            for (int y = 0; y < loop; ++y){
                b[x * loop + y] = 0;
            }
        }

        loop_index = -1;
        #pragma acc kernels loop gang num_gangs(num_gangs)
        for (int x = 0; x < loop; ++x){
            loop_index = x;
            for (int y = 0; y < num_gangs; ++y){
                b[loop_index + y * loop + 0] = 1;
            }
        }
    }

    for (int x = 0; x < loop; ++x){
        clause_err = 0;
        for (int y = 0; y < num_gangs; ++y){
            clause_err += fabsb(b[x + y * loop + 0] - 1) > PRECISION;
        }
        if (clause_err != 0){
            err += clause_err;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:parallel,construct-independent,V:2.0-3.0
int test3(){
    int err = 0;
    int clause_err = 0;
    int num_gangs = acc_get_num_gangs();
    int num_gangs_clause[3] = {3, 1, 2};

    real_t * a = (real_t *)malloc(num_gangs * loop * sizeof(real_t));
    real_t * b = (real_t *)malloc(num_gangs * loop * sizeof(real_t));

    for (int x = 0; x < num_gangs; ++x)
        for (int y = 0; y < loop; ++y){
            a[x * loop + y] = rand() / (real_t)(RAND_MAX / 10);
        }

    #pragma acc data copyin(a[0:num_gangs*loop]) create(b[0:num_gangs*loop])
    {
        for (int x = 0; x < num_gangs; ++x){
            for (int y = 0; y < loop; ++y){
                b[x * loop + y] = 0;
            }
        }

        #pragma acc parallel num_gangs(3, 1, 2)
        {
            #pragma acc loop gang
            for (int x = 0; x < loop; ++x){
                int mx = 0;
                for (int y = 0; y < num_gangs; ++y){
                    mx += fabsb(a[x + y * loop] - 1);
                }
                b[x + 1 * loop] = mx;
            }
        }
    }

    for (int x = 0; x < loop; ++x){
        clause_err = 0;
        for (int y = 0; y < num_gangs; ++y){
            clause_err += fabsb(b[x + 1 * loop] - (1 * num_gangs)) > PRECISION;
        }
        if (clause_err != 0){
            err += clause_err;
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
#ifndef T3
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test3();
    }
    if (failed != 0){
        failcode = failcode + (1 << 2);
    }
#endif
    return failcode;
}