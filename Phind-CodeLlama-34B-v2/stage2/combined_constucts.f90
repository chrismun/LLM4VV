#ifndef T1
!T1:combined constucts,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(LOOPCOUNT) :: a, b, c

        !$acc parallel loop
        DO i = 1, LOOPCOUNT
          a(i) = 3.14
        END DO
        !$acc end parallel loop

        !$acc serial loop
        DO i = 1, LOOPCOUNT
          b(i) = 3.14
        END DO
        !$acc end serial loop

        !$acc kernels loop
        DO i = 1, LOOPCOUNT
          c(i) = 3.14
        END DO
        !$acc end kernels loop

        DO i = 1, LOOPCOUNT
          IF (a(i) .ne. 3.14 .or. b(i) .ne. 3.14 .or. c(i) .ne. 3.14) THEN
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