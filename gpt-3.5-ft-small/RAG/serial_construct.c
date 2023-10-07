int i = 1; i < n; ++i)
    A[i] = A[i-1] + 1;
}
#pragma acc serial
{
  for (int i = 1; i < n; ++i)
    B[i] = B[i-1] + 1;
}