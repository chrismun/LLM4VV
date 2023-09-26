#ifndef T1
!T1:wait directive,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: async1, async2
        REAL(8), DIMENSION(10) :: a, b, c

        a = 1.0
        b = 2.0
        c = 0.0

        !$acc enter data copyin(a, b, c)

        !$acc parallel async(async1)
          c = a + b
        !$acc end parallel

        !$acc parallel async(async2)
          c = a - b
        !$acc end parallel

        !$acc wait(async1, async2)

        !$acc exit data delete(a, b, c)

        IF (ANY(c .NE. 1.0)) THEN
          errors = errors + 1
        END IF

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