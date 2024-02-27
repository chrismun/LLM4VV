! This program is a test for the OpenACC parallel construct wait clause.
! It returns 0 if the target feature is working correctly, and a non-zero otherwise.

!T1:parallel construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: arr1(N), arr2(N)
        INTEGER :: errors = 0, i

        ! Initialize arrays
        arr1 = 1
        arr2 = 0

        !$acc parallel loop copy(arr1) copyout(arr2) async(1)
        DO i = 1, N
          arr2(i) = arr1(i) + 1
        END DO

        !$acc wait(1)

        ! Check results
        DO i = 1, N
          IF (arr2(i) /= 2) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        USE OPENACC
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

        CALL EXIT (failcode)
      END PROGRAM main