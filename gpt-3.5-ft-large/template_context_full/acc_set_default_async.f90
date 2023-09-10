#ifndef T1
!T1:acc set default async,V:2.7-2.3
        LOGICAL FUNCTION test1()
          USE OPENACC
          IMPLICIT NONE
          INCLUDE "acc_testsuite.Fh"
        
          INTEGER :: errors = 0


          acc_set_default_async(1)

          IF (errors .eq. 0) THEN
            test1 = .FALSE.
          ELSE
            test1 = .TRUE.
          END IF
        END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM