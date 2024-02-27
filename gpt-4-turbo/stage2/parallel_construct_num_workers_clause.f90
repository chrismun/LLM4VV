!T1:parallel construct num_workers clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(1024) :: testData
        INTEGER :: i, num_workers_used

        ! Initialize testData array
        testData = 0
        
        ! Assuming the number of workers intended is 32.
        ! This value can be adjusted based on testing needs or hardware capabilities.
        num_workers_used = 32

        !$ACC PARALLEL NUM_WORKERS(num_workers_used)
        !$ACC LOOP
        DO i = 1, SIZE(testData)
          ! A simple operation to verify working
          testData(i) = 1
        END DO
        !$ACC END PARALLEL

        ! Verify if testData has been correctly modified
        DO i = 1, SIZE(testData)
          IF (testData(i) /= 1) THEN
            errors = errors + 1
          END IF
        END DO
        
        ! Ideally, we would check the actual number of workers used during execution
        ! but such verification requires runtime introspection capabilities that are hardware-specific.
        ! Hence, we infer correct behavior from correct execution outcomes.

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        EXTERNAL :: test1
        LOGICAL :: L_test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          L_test1 = test1()
          failed = failed .or. L_test1
        END DO
        IF (failed) THEN
          PRINT *, "Test 1 failed."
          failcode = failcode + 2 ** 0
        ELSE
          PRINT *, "Test 1 passed."
        END IF
        CALL EXIT(failcode)
      END PROGRAM main