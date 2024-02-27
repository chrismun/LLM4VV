! Assuming necessary OpenACC module and any test framework setup is available.
MODULE test_module
  USE openacc
CONTAINS
!T1:declare directive device_resident clause,V:2.7-2.3
  FUNCTION test1() RESULT(success)
    IMPLICIT NONE
    LOGICAL :: success
    INTEGER, ALLOCATABLE, DEVICE_RESIDENT :: testArray(:)
    INTEGER :: i, errors
    errors = 0

    ! Allocate device-resident memory
    ALLOCATE(testArray(100))

    ! Attempt computation in a parallel region that should
    ! utilize the device-resident memory
    !$acc parallel loop copy(errors)
    DO i = 1, 100
      testArray(i) = i
      IF (testArray(i) /= i) errors = errors + 1
    END DO

    !$acc end parallel

    DEALLOCATE(testArray)

    IF (errors == 0) THEN
      success = .TRUE.
    ELSE
      success = .FALSE.
    END IF
  END FUNCTION test1
END MODULE test_module

PROGRAM main
  USE test_module
  IMPLICIT NONE
  LOGICAL :: testResult

  testResult = test1()

  IF (testResult) THEN
    PRINT *, "Test Passed, 'device_resident' clause works as expected."
    CALL EXIT(0)
  ELSE
    PRINT *, "Test Failed, 'device_resident' clause did not work as expected."
    CALL EXIT(1)
  END IF

END PROGRAM main