#include <stdio.h>
#include <openacc.h>

int main() {
    int N = 100;
    float *x = (float*)malloc(N*sizeof(float));

    /* Initialize x on the host*/
    for(int i=0; i<N; i++) {
      x[i] = 1.0f;
    }

    /* Ensure data does not exist on the device */
    if(acc_is_present(x, N*sizeof(float))){
      printf("Error: Data found on device before it's been moved there\n");
      return 1;
    }

    /* Move data to device */
    #pragma acc data copyin(x[0:N])
    {
        /* Check data is now on the device */
        if(!acc_is_present(x, N*sizeof(float))){
          printf("Error: Data not found on device after moved there\n");
          return 1;
        }
    }

    /* Check data is no longer on the device */
    if(acc_is_present(x, N*sizeof(float))){
        printf("Error: Data found on device after it's been removed\n");
        return 1;
    }

    printf("All acc_is_present() tests passed.\n");
    
    free(x);

    return 0;