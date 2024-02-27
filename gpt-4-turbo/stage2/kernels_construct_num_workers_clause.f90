! Include necessary modules for OpenACC
MODULE test_utils
  USE openacc
  IMPLICIT NONE
CONTAINS
  LOGICAL FUNCTION verify_operation(array, size)
    INTEGER, INTENT(IN) :: size
    INTEGER, DIMENSION(size), INTENT(IN) :: array
    INTEGER :: i
    verify_operation = .TRUE.
    DO i = 1, size
      IF (array(i) /= i**2) THEN
        verify_operation = .FALSE.
        EXIT
      END IF
    END DO
  END FUNCTION verify_operation
END MODULE test_utils

!T1:kernels construct num_workers clause,V:2.7-2.3
PROGRAM main
  USE OPENACC
  USE test_utils
  IMPLICIT NONE
  INTEGER, PARAMETER :: arrSize = 10000
  INTEGER :: errors = 0
  INTEGER :: i
  INTEGER, DIMENSION(arrSize) :: testArray
  
  ! Initializing the array
  DO i = 1, arrSize
    testArray(i) = i
  END DO
  
  ! Applying the kernels directive with num_workers
  !$acc kernels num_workers(64)
  DO i = 1, arrSize
    testArray(i) = testArray(i) ** 2
  END DO
  !$acc end kernels
  
  ! Verifying the operation
  IF (.NOT. verify_operation(testArray, arrSize)) THEN
    PRINT *, "Test failed: The operation within kernels did not execute as expected."
    errors = errors + 1
  END IF
  
  IF (errors == 0) THEN
    PRINT *, "Test passed: num_workers clause within kernels executed correctly."
  ELSE
    PRINT *, "Test encountered errors."
  END IF

  CALL EXIT(errors)
END PROGRAM main