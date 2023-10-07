! test_openacc_cache.f90
PROGRAM cache_test
  USE OPENACC
  IMPLICIT NONE
  INTEGER, DIMENSION(100) :: a, b
  INTEGER :: i, err, sum1, sum2

  a = 1
  b = 2

  ! Test the cache directive
  sum1 = 0; sum2 = 0
  !$ACC PARALLEL LOOP cache(a(10:90), b(10:90))
  DO i=10, 90
    sum1 = sum1 + a(i)
    sum2 = sum2 + b(i)
  END DO
  !$ACC END PARALLEL LOOP

  ! Check results
  IF (sum1==81 .AND. sum2==162) THEN
    err = 0 ! Working properly.
  ELSE
    err = 1 ! Something is wrong.
  END IF

  IF (err != 0) THEN
    PRINT *, "ERROR: Test failed"
  ELSE
    PRINT *, "SUCCESS: Test passed"
  END IF 

END PROGRAM cache_test