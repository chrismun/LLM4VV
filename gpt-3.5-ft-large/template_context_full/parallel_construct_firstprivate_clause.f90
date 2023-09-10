#ifndef T1
!T1:parallel construct firstprivate clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER,DIMENSION(LOOPCOUNT):: a
        INTEGER :: x

        !initilization
        SEEDDIM(1) = 1
        #if IS_LOOP_TEST
        INIT_SEED(1)
        #else
        INIT_SEED(LOOPCOUNT)
        #endif
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)

        !$acc parallel copy(a(1:LOOPCOUNT))
          !$acc loop gang
          DO x = 1, LOOPCOUNT
            a(x) = -1
          END DO
        !$acc end parallel

        !$acc parallel firstprivate(a(1))
          !$acc loop gang
          DO x = 2, LOOPCOUNT
            a(x) = a(x - 1) + 1
          END DO
        !$acc end parallel

        !$acc parallel loop gang present(a(1:LOOPCOUNT))
        DO x = 2, LOOPCOUNT
          IF(a(x) .eq. a(x - 1)) THEN
            errors = 1
          END IF
        END DO
        !$acc end parallel loop

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