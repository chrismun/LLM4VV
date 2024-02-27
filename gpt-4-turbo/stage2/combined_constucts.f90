! Example: Verifying OpenACC Combined Constructs 
! Fortran code to test the functionality of !$acc parallel loop
! --------------------------------------------------------------------------
! File: acc_parallel_loop_test.F90

MODULE acc_test_module
  USE openacc
  INTEGER, PARAMETER :: N = 10000
  CONTAINS
    LOGICAL FUNCTION test_parallel_loop()
      INTEGER :: i
      INTEGER, DIMENSION(N) :: a
      INTEGER :: sum, expected_sum

      ! Initialize array 
      DO i= 1, N
        a(i) = i
      END DO

      sum = 0
      expected_sum = N * (N + 1) / 2

      ! Parallel Summation using combined constructs
      !$acc parallel loop reduction(+:sum)
      DO i = 1, N
        sum = sum + a(i)
      END DO
      !$acc end parallel loop

      IF (sum == expected_sum) THEN
        test_parallel_loop = .TRUE.
      ELSE
        test_parallel_loop = .FALSE.
      END IF
    END FUNCTION test_parallel_loop
END MODULE acc_test_module

PROGRAM main
  USE acc_test_module
  LOGICAL :: result

  result = test_parallel_loop()

  IF (result) THEN
    PRINT *, "Test PASSED. Parallel Loop construct works as expected."
  ELSE
    PRINT *, "Test FAILED. Parallel Loop construct does not work as expected."
  END IF

END PROGRAM main