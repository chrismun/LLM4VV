#ifndef T1_ACC_ASYNC_TEST
!T1_ACC_ASYNC_TEST:acc async test, V:2.7-2.3
      LOGICAL FUNCTION test1_acc_async_test()
        USE OPENACC
        IMPLICIT NONE

        ! Required for acc_handle kind
        INTEGER, PARAMETER :: acc_handle_kind = 8
        INTEGER(acc_handle_kind) :: wait_arg
        INTEGER :: dev_num

        ! Load device number, wait argument and error condition
        dev_num = 0
        wait_arg = 1
        errors = 0


        ! A simulated async operation
        !$ACC PARALLEL NUM_GANGS(1) VECTOR_LENGTH(1) ASYNC(wait_arg)
        !$ACC END PARALLEL

        ! This should return false since async operation is in progress
        IF (acc_async_test(wait_arg)) errors = errors + 1

        !$ACC WAIT(wait_arg)

        ! This should return true since async operation has completed
        IF (.NOT. acc_async_test(wait_arg)) errors = errors + 1

        ! If no errors were encountered, the function passes
        IF (errors .eq. 0) THEN
          test1_acc_async_test = .TRUE.
        ELSE
          test1_acc_async_test = .FALSE.
        END IF

      END FUNCTION test1_acc_async_test
#endif

PROGRAM main
    IMPLICIT NONE
    INTEGER :: failcode, testrun
    LOGICAL :: failed
#ifndef T1_ACC_ASYNC_TEST
    LOGICAL :: test1_acc_async_test
#endif
    failed = .FALSE.
    failcode = 0
#ifndef T1_ACC_ASYNC_TEST
    DO testrun = 1, NUM_TEST_CALLS
      failed = failed .or. test1_acc_async_test()
    END DO
    IF (failed) THEN
      failcode = failcode + 2 ** 0
      failed = .FALSE.
    END IF
#endif
    CALL EXIT (failcode)
END PROGRAM main