! Example code snippet for testing OpenACC data construct create clause.
MODULE test_module
  USE openacc
  IMPLICIT NONE
CONTAINS
  FUNCTION test_create_clause() RESULT(success)
    LOGICAL :: success
    INTEGER, DIMENSION(:), ALLOCATABLE :: test_array
    INTEGER :: i, errors
    INTEGER, PARAMETER :: array_size = 1000
    INTEGER, PARAMETER :: test_val = 123

    errors = 0
    ALLOCATE(test_array(array_size))

    ! Initialize the array with zeros
    test_array = 0

    !$acc enter data create(test_array)

    !$acc parallel loop
    DO i = 1, array_size
      test_array(i) = test_val
    END DO

    !$acc exit data copyout(test_array)

    ! Check if the array contains the correct values
    DO i = 1, array_size
      IF (test_array(i) /= test_val) THEN
        errors = errors + 1
      END IF
    END DO

    IF (errors == 0) THEN
      success = .TRUE.
    ELSE
      success = .FALSE.
    END IF

    DEALLOCATE(test_array)
  END FUNCTION test_create_clause
END MODULE test_module

PROGRAM main
  USE test_module
  IMPLICIT NONE

  LOGICAL :: result

  result = test_create_clause()

  IF (result) THEN
    PRINT *, "OpenACC create clause test PASSED."
    CALL EXIT(0)
  ELSE
    PRINT *, "OpenACC create clause test FAILED."
    CALL EXIT(1)
  END IF
END PROGRAM main