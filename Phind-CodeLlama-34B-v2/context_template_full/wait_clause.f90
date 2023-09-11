#ifndef T1
!T1:wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(LOOPCOUNT) :: a, b, c

        !$acc data copy(a(1:LOOPCOUNT), b(1:LOOPCOUNT), c(1:LOOPCOUNT))
          !$acc parallel loop async(1)
          DO i = 1, LOOPCOUNT
            a(i) = 3.14
          END DO

          !$acc parallel loop async(2)
          DO i = 1, LOOPCOUNT
            b(i) = 42.0
          END DO

          !$acc parallel loop async(3)
          DO i = 1, LOOPCOUNT
            c(i) = a(i) * b(i)
          END DO

          !$acc wait(1, 2, 3)
        !$acc end data

        DO i = 1, LOOPCOUNT
          IF (ABS(c(i) - 128.616) .gt. PRECISION) THEN
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