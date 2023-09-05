#ifndef T1
//T1:parallel,data,devonly,V:2.0-2.7
int test1(real_t** a, real_t** b, real_t*** b_ptr_change)
{
    int err = 0;
    srand(SEED);

    real_t* d = (real_t*)malloc(n * sizeof(real_t));
    *a = (real_t*)malloc(n * sizeof(real_t));
    *b = (real_t*)malloc(n * sizeof(real_t));
    *b_ptr_change = b; // Change pointer we pass back to kernel

    for (int x = 0; x < n; ++x)
    {
        (*a)[x] = rand() / (real_t)(RAND_MAX / 10);
        (*b)[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc data copyin((*a)[0:n]) create((*b_ptr_change)[0:n]) present(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang vector
            for (int x = 0; x < n; ++x)
            {
                (*b_ptr_change)[x] = (*a)[x];
                d[x] = (*b)[x] + d[x];
            }
        }
    }

    for (int x = 0; x < n; ++x)
    {
        if (fabs((*a)[x] - (*b_ptr_change)[x]) > PRECISION || fabs(d[x] - (*b_ptr_change)[x]) > PRECISION)
        {
            err += 1;
            break;
        }
    }

    free(d);
    return err;
}

#endif

int main()
{
    int failcode = 0;
    int failed;
#ifndef T1
    real_t* a, *b;
    real_t** b_ptr_change;
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x)
    {
        b_ptr_change = &b;
        failed = failed + test1(&a, &b, &b_ptr_change);
    }

    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }

#endif
    return failcode;
}