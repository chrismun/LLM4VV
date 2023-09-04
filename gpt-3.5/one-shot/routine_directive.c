#include "stdio.h"
#include "stdlib.h"

void add(int num1, int num2, int *sum){
   *sum = num1 + num2;
}

int main(){
   int a = 5, b = 10, sum = 0;
   #pragma acc routine
   add(a, b, &sum);
   printf("Sum: %d\n", sum);
   return 0;
}