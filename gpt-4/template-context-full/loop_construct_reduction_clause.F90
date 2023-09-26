!> @file test_openacc_reduction.f90
!> @brief Fortran test for OpenACC reduction clause.

MODULE reduction_test
  USE openacc
  IMPLICIT NONE
  INTEGER, PARAMETER :: N = 1024
  INTEGER :: array(N)
END MODULE

!> @brief Main test function
SUBROUTINE test_openacc_reduction()
  USE reduction_test
  INTEGER :: i, sum, reference_sum

  ! Initialize the array
  array(:) = 1

  ! Perform the reduction using the standard Fortran approach
  reference_sum = SUM(array(:))

  ! Begin the OpenACC parallel region
  !$ACC PARALLEL LOOP COPYIN(array) REDUCTION(+:sum)
  DO i = 1, N
    sum = sum + array(i)
  END DO
  !$ACC END PARALLEL LOOP

  ! Verify that the results match
  IF (sum .NE. reference_sum) THEN
    PRINT *, "Test failed: sum = ", sum, ", reference_sum = ", reference_sum
  ELSE
    PRINT *, "Test passed"
  END IF
END SUBROUTINE test_openacc_reduction

PROGRAM main
  CALL test_openacc_reduction()
END PROGRAM main