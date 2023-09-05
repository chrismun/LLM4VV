#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void acc_hostptr_test() {
  int size = 10;
  int *data = (int *) malloc(size * sizeof(int));

  #pragma acc enter data create(data[:size])

  for (int i = 0; i < size; i++) {
    data[i] = i;
  }

  #pragma acc exit data copyout(data[:size])

  for (int i = 0; i < size; i++) {
    printf("data[%d] = %d\n", i, data[i]);
  }

  free(data);
}

int main() {
  acc_hostptr_test();

  return 0;
}