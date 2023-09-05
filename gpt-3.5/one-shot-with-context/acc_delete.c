#ifndef T1
// T1: delete:data
int test1()
{
    int err = 0;

    int *a = (int *)malloc(n * sizeof(int));

    #pragma acc enter data create(a[0:n])

    #pragma acc parallel present(a[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; i++)
            a[i] = i;
    }

    #pragma acc delete(a[0:n])

    #pragma acc exit data copyout(a[0:n])

    for (int i = 0; i < n; i++)
    {
        if (a[i] != i)
        {
            err += 1;
            break;
        }
    }

    free(a);

    return err;
}
#endif

int main()
{
    int failcode = 0;

#ifndef T1
    int failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++)
    {
        failed += test1();
    }
    if (failed != 0)
    {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}