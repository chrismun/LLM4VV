! Assuming acc_testsuite.Fh sets up the necessary environment
! and provides utility functions/macros for testing.

!T1:acc_copyout,V:2.7-2.3

! Function to test acc_copyout
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE

        INTEGER, DIMENSION(:), ALLOCATABLE :: hostArray
        INTEGER :: i, arraySize, errors
        errors = 0
        arraySize = 100

! Allocate and initialize the array on the host
        ALLOCATE(hostArray(arraySize))
        hostArray = 0

! Update and copy out the array using OpenACC
! Directive to run in device and modify array values
        !$acc data copyout(hostArray)
        !$acc parallel loop
        DO i=1, arraySize
          hostArray(i) = i
        END DO
        !$acc end data

! Verify changes were reflected on the host
        DO i=1, arraySize
          IF (hostArray(i) /= i) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE. ! Presuming .FALSE. denotes success here
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"

        LOGICAL :: test1

        failed = .FALSE.
        failcode = 0

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO

        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF

        CALL EXIT(failcode)
      END PROGRAM main