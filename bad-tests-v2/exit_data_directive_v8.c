void test_exit_data() 
{
int i = 0;
real_t *Y_data = (real_t *)acc_malloc(n * sizeof(real_t));
real_t *tempX;
for (int x = 0; x < n; ++x) {
  tempX = &(X_data[x * m]);
  Y_data[i] = 0.0;
  for (int y = 0; y < m; ++y) {
    Y_data[i] += tempX[y];
  }
  ++i;
}
#pragma acc enter data copyin(Y_data[0:n])
#pragma acc exit data delete(tempX)
return;
}