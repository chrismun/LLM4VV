#ifndef T1
!T1:serial construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), DIMENSION(LOOPCOUNT, 10):: a, b, c

        !Initialization
        SEEDDIM(1) = 1
        #if REAL_SIZE == 4
        CALL RANDOM_SEED(PUT=(/1, SEEDDIM(1)/))
        #endif
        #if REAL_SIZE == 8
        CALL RANDOM_SEED(PUT=(/1, 1, SEEDDIM(1), SEEDDIM(2)/))
        #endif
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc enter data copyin(a(1:LOOPCOUNT, 1:10), b(1:LOOPCOUNT, 1:10)) create(c(1:LOOPCOUNT, 1:10))
        DO j = 1, 10
          DO test = 1, LOOPCOUNT
            c(test, j) = a(test, j) + b(test, j)
          END DO
          !$acc data copy(c(1:LOOPCOUNT, j))
            !$acc serial loop wait(j-1) private(a, b)
            DO i = 1, LOOPCOUNT
              a(i, j) = acc_get_value(c(i, j))
              b(i, j) = a(i, j)
            END DO
          !$acc end data
          DO test = 1, LOOPCOUNT
            IF (abs(c(test, j) - (a(test, j) + b(test, j))) .gt. (10 * PRECISION)) THEN
              errors = errors + 1
            END IF
          END DO
        END DO
        !$acc exit data copyout(c(1:LOOPCOUNT, 1:10))

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