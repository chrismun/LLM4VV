!T1:acc wait any,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        INTEGER :: i, ierr
        integer(acc_handle_kind) :: wait_arg(1)

        ! initialize the handle
        !$acc declare create(wait_arg)

        !$acc region
          !generate a random number in each thread to
          !simulate the need to set the asynchronous
          !argument in parallel code
          !$acc do
          DO i = 1, LOOP_COUNT
            wait_arg(1) = i
          END DO
        !$acc end region

        ! wait for what ever interation ends last
        !$acc wait any(wait_arg)

        DO i = 1, LOOP_COUNT
          ! test that all loop iterations are 
          ! finished before exiting the region
          IF (wait_arg(1) .eq. i) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
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