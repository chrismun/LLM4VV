#ifndef T1
!T1:kernels construct async clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c
        INTEGER:: i, x
        LOGICAL :: AsyncsDevice1Present, AsyncsDevice2Present

        !Initilization
        SEEDDIM(1) = 1
#       ifdef SEED
        SEEDDIM(1) = SEED
#       endif
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !Determine if Async is supported
        AsyncsDevice1Present = .FALSE.
        AsyncsDevice2Present = .FALSE.
        !$acc enter data copyin(c(1:LOOPCOUNT))
        !$acc data present(c(1:LOOPCOUNT)) copyout(c(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop
            DO i = 1, LOOPCOUNT
              c(i) = c(i) + a(i) + b(i)
            END DO
          !$acc end parallel
        !$acc end data
        !$acc exit data delete(c(1:LOOPCOUNT))

        !$acc parallel host(AsyncsDevice1Present, AsyncsDevice2Present) 
          !$acc loop gang
          DO x = 1, 1
            !$acc loop worker
            DO i = 1, LOOPCOUNT
              c(i) = 1
            END DO
          END DO
        !$acc end parallel

        !$acc enter data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT))
        !$acc data present(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(c(1:LOOPCOUNT))
          !$acc parallel 
            !$acc loop
            DO i = 1, LOOPCOUNT
	      c(i) = c(i) + a(i) + b(i)
            END DO 
          !$acc end parallel
        !$acc end data
        a(1) = 0
        b(1) = 0

        !$acc data copyin(a(1:LOOPCOUNT), b(1:LOOPCOUNT)) copyout(c(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop
            DO i = 1, LOOPCOUNT
              c(i) = c(i) - (a(i) + b(i))
            END DO
          !$acc end parallel
        !$acc end data

        CALL compare(c(1:LOOPCOUNT), a, b, c_mult, errors)

        test1 = errors
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