! Test to verify compiler implementation of the OpenACC specification for acc_get_default_async in Fortran

!T1:acc_get_default_async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER(acc_handle_kind) :: default_async, test_async

        ! Initialize a specific async queue number for testing
        test_async = 5

        ! Set the specific async queue number as default
        CALL acc_set_default_async(test_async)

        ! Retrieve the default async value using acc_get_default_async
        default_async = acc_get_default_async()

        ! Verify if the retrieved default async matches the test_async
        IF (default_async .ne. test_async) THEN
          errors = errors + 1
        END IF

        ! Reset the default async to prevent side effects on other tests
        CALL acc_set_default_async(acc_async_noval)

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