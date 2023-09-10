!T1:acc set default async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.F90"
        
        INTEGER :: errors = 0
        INTEGER(ACC_HANDLE_KIND) :: async_arg
        LOGICAL :: status
        INTEGER :: a, b
        
        a = 1
        async_arg = acc_async_sync

        CALL acc_set_default_async(async_arg)
        
        ! check if the async_arg has been set
        IF (acc_get_default_async() .ne. async_arg) THEN
          errors = errors + 1
        END IF
        
        !$acc parallel async
        a = 2
        !$acc end parallel

        b = acc_async_test_all()
        
        ! delay to allow work to be done
        CALL sleep(1)
        
        IF (b .eq. 0 .and. a .ne. 2) THEN
          errors = errors + 1
        END IF

        !$acc wait

        IF (a .ne. 2) THEN
          errors = errors + 1
        END IF

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.F90"
#ifndef T1
        LOGICAL :: test1
#endif
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