#pragma acc kernels
{
    // Some computation
    if (some_condition) {
        #pragma acc shutdown
    }
}