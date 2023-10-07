#ifndef T1
#define DATA_SIZE 1024
#define NUM_TESTS 10
int test1()
{
    int err = 0;

    float *a = (float *)malloc(DATA_SIZE * sizeof(float));
    float *b = (float *)malloc(DATA_SIZE * sizeof(float));
    float *c = (float *)malloc(DATA_SIZE * sizeof(float));
    float *d = (float *)malloc(DATA_SIZE * sizeof(float));

    for (int i = 0; i < DATA_SIZE; ++i)
    {
        a[i] = (float)i;
        b[i] = (float)i;
        c[i] = 0.0f;
        d[i] = 0.0f;
    }

    #pragma acc data copyin(a[0:DATA_SIZE], b[0:DATA_SIZE]), create(c[0:DATA_SIZE]) \
        copyout(d[0:DATA_SIZE])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < DATA_SIZE; ++i)
            {
                c[i] = a[i] + b[i];
            }

            #pragma acc loop wait
            for (int i = 0; i < DATA_SIZE; ++i)
            {
                d[i] = c[i] * 2.0f;
            }
        }
    }

    for (int i = 0; i < DATA_SIZE; ++i)
    {
        if (fabs(d[i] - (a[i] + b[i]) * 2.0f) > PRECISION)
        {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);

    return err;
}
#endif

int main()
{
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int i = 0; i < NUM_TESTS; ++i)
    {
        failed += test1();
    }

    if (failed != 0)
    {
        failcode = 1;
    }
#endif

    return failcode;
}