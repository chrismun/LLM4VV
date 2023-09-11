#ifndef T1
!T1:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER(KIND=ACC_HANDLE_KIND) :: async1, async2
        REAL(KIND=8), DIMENSION(100) :: a, b, c

        a = 1.0
        b = 2.0
        c = 0.0

        !$acc enter data copyin(a, b, c)

        !$acc parallel async(async1)
          c = a + b
        !$acc end parallel

        !$acc wait(async1)

        !$acc update self(c)

        !$acc enter data create(a, b, c)

        !$acc parallel async(async2)
          c = a * b
        !$acc end parallel

        !$acc wait_async(async1, async2)

        !$acc update self(c)

        !$acc exit data delete(a, b, c)

        DO i = 1, 100
          IF (c(i) .ne. 3.0) THEN
            errors = errors + 1
          END IF
        END DO

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