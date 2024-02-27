!T1:wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE openacc
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: testData
        INTEGER :: i

        ALLOCATE(testData(100))
        testData = 0

        ! Implementing parallel operations with the wait clause
        !$acc parallel loop async(1)
        DO i = 1, 100
          testData(i) = i
        END DO

        !$acc wait(1)

        !$acc parallel loop async(1)
        DO i = 1, 100
          testData(i) = testData(i) * 2
        END DO

        !$acc wait(1)

        ! Verify the wait clause worked by checking changes were applied in sequence
        DO i = 1, 100
          IF (testData(i) /= i * 2) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF

        DEALLOCATE(testData)
      END

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
        CALL EXIT (failcode)
      END PROGRAM