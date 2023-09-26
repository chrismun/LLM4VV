!T1:acc get default async, V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER(KIND=acc_handle_kind) :: def_async_val

        !$ACC PARALLEL
            def_async_val = acc_get_default_async()
        !$ACC END PARALLEL
      
        !print *,"Default Async Value: ", def_async_val

        IF (( def_async_val < 0) .OR. (def_async_val > 4)) THEN
          errors = errors + 1
        END IF

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