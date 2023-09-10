#ifndef T1
!T1:loop construct auto clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10 * LOOPCOUNT) :: a, b, c, d
        REAL(2), DIMENSION(10 * LOOPCOUNT) :: randoms
        REAL(2), DIMENSION(LOOPCOUNT) :: lrand, nrand
        REAL(2) :: none
        INTEGER :: x


        !Initilization
        SEEDDIM(1) = 1
        #if _OPENACC && defined(SEED)
        SEEDDIM(1) = SEED
        #endif
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(randoms)
        none = 0
        a = 1
        c = 1
        d = 1
        DO x = 1, 10 * LOOPCOUNT
          b(x) = x
        END DO

        !$acc data copyin(randoms(1:10*LOOPCOUNT)) create(lrand(1:LOOPCOUNT)) copy(nrand(1:LOOPCOUNT)) copyout(a(1:10*LOOPCOUNT), b(1:10*LOOPCOUNT), c(1:10*LOOPCOUNT), d(1:10*LOOPCOUNT))
          !$acc parallel
            !$acc loop independent
            DO x = 1, 10 * LOOPCOUNT
              a(x) = (c(x) * b(x) + d(x)) / 2
              lrand(x .mod. LOOPCOUNT + 1) = randoms(x)
            END DO
            !$acc loop auto
            DO x = 1, 10 * LOOPCOUNT
              nrand(x .mod. LOOPCOUNT + 1) = (c(x) * b(x) + d(x)) / 2
            END DO
            !$acc loop seq
            DO x = 1, LOOPCOUNT
              IF (abs(lrand(x) - nrand(x)) .gt. PRECISION) THEN
                errors = errors + 1
              END IF
            END DO
          !$acc end data
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