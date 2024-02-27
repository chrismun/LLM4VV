! This test requires an OpenACC environment and might need specific
! compiler flags and/or libraries to correctly interpret OpenACC directives.
! Make sure to adjust the compilation command accordingly.

! The ACC_SET_DEFAULT_ASYNC API functionality is mimicked using a set directive in this test.

!T1:set directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: old_async, new_async, queried_async

        ! Query the current default async value
        old_async = acc_get_default_async()

        ! Set a new default async queue using the set directive
        new_async = 5  ! Assuming 5 is a valid async queue number for the environment
        !$acc set default_async(new_async)

        ! Query the default async value after setting it
        queried_async = acc_get_default_async()

        ! Check if the new async value is set correctly
        IF (queried_async /= new_async) THEN
          errors = errors + 1
        END IF

        ! Optionally, reset the default async to its old value to clean up
        !$acc set default_async(old_async)

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