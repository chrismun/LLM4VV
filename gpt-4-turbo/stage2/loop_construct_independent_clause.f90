! Example code to test OpenACC's independent loop construct in Fortran
! Make sure you have appropriate support for OpenACC in your compiler

MODULE acc_test_module
  USE OPENACC
  IMPLICIT NONE
CONTAINS
  LOGICAL FUNCTION test_independent_clause()
    INTEGER, DIMENSION(:), ALLOCATABLE :: test_array
    INTEGER :: i, sum, expected_sum
    INTEGER, PARAMETER :: array_size = 1000
    sum = 0
    expected_sum = 0

    ! Allocate and initialize the test array
    ALLOCATE(test_array(array_size))
    
    ! Initialize test_array in parallel ensuring the loop iterations are independent
    !$acc parallel loop independent
    DO i = 1, array_size
      test_array(i) = 1
    END DO
    !$acc end parallel

    ! Use reduction to sum the elements in parallel
    !$acc parallel loop reduction(+:sum)
    DO i = 1, array_size
      sum = sum + test_array(i)
    END DO
    !$acc end parallel

    DEALLOCATE(test_array)

    ! Expected sum is the array_size since all elements are 1
    expected_sum = array_size

    ! Check if the sum is as expected
    IF (sum == expected_sum) THEN
      test_independent_clause = .FALSE.
    ELSE
      test_independent_clause = .TRUE.
    END IF
  END FUNCTION test_independent_clause

END MODULE acc_test_module

! Main program to execute the tests
PROGRAM main
  USE acc_test_module
  IMPLICIT NONE
  LOGICAL :: failed

  failed = test_independent_clause()

  ! If failed is FALSE, the test passed, otherwise it failed.
  IF (failed) THEN
    PRINT *, "Test failed. The independent clause might not be working correctly."
    CALL EXIT(1)
  ELSE
    PRINT *, "Test passed. The independent clause is working as expected."
    CALL EXIT(0)
  END IF
END PROGRAM main