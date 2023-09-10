#ifndef T1
!T1:loop construct seq clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER,DIMENSION(LOOPCOUNT):: a, a_copy
        REAL(2.0, 4.0)::coeff
        REAL*8, DIMENSION(5*LOOPCOUNT)::random_number
        REAL*8:: sum = 0
        INTEGER :: x
        SEEDDIM(1)=1
        SEED(1)=627
        
        CALL SRAND48(627)
        
        a_copy = a
        DO x = 1, 5 * LOOPCOUNT
          CALL DRAND48(random_number(x))
        END DO
        DO x = 1, LOOPCOUNT
          a(x) = 5
        END DO
        
        !$acc data copy(a(1:LOOPCOUNT))
          !$acc serial
            !$acc loop seq
            DO x = 1, LOOPCOUNT
              a(x) = 1
            END DO
          !$acc end serial
        !$acc end data
        DO x = 1, LOOPCOUNT
          sum = sum + (a(x) - 1)
        END DO
        DO x = 1, LOOPCOUNT
          sum = sum + a(x)
        END DO
        DO x = 1, 5 * LOOPCOUNT
          sum = sum + (random_number(x) - a(x/5))
        END DO
        IF (sum .neq. 0) THEN
          errors = errors + 1
        END IF

        a = a_copy
        IF (errors .lt. 1) THEN
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