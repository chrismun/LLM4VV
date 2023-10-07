#ifndef T1
!T1:host_data construct if_present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER:: x,r
        LOGICAL,DIMENSION(1):: devtest
        devtest(1) = .TRUE.
        
        !$acc enter data copyin(devtest(1:1))
        
        SEEDDIM(1) = 1
#       ifdef AMPI
        SEEDDIM(2) = MPISIZE
#       else
        SEEDDIM(2) = 1
#       endif
        CALL RANDOM_SEED(PUT=devtest(1), SOURCE=devtest(1), SIZE=1)
        CALL RANDOM_NUMBER(a)
        IF (DATA_TEST_MODE) THEN
          b(1:LOOPCOUNT) = 1
        ELSE
          CALL RANDOM_NUMBER(b)
        END IF
        c = 0
        
        !$acc data create(c(1:LOOPCOUNT))
          DO r = 0, PRESENT_or_not_AMPF(1, devtest)
            !$acc parallel
            IF (devtest(1)) THEN
              !$acc loop
              DO x = 1, LOOPCOUNT
                c(x) = c(x) + a(x) + b(x)
              END DO
            END IF
            !$acc end parallel
          END DO
          !$acc host_data if_present(c(1:LOOPCOUNT))
            DO x = 1, LOOPCOUNT
              IF (abs(c(x) - (a(x) + b(x))) .gt. PRECISION) THEN
                errors = errors + 1
              END IF
            END DO
          !$acc end host_data
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