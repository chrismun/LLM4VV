#ifndef T1
!T1:kernels construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(30,30) :: a, b, c, d, tmp
        INTEGER :: x, y
        REAL(8) :: av

        !Initialise the arrays
        SEEDDIM(1) = 1
        #ifdef SEED
        SEEDDIM(1) = SEED
        #endif
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)
        tmp = 0
        av = 0
        !$acc data copyin(a(1:30, 1:30), b(1:30, 1:30), c(1:30, 1:30)) copyout(d(1:30, 1:30))
          DO y = 1, 30
            !$acc parallel
              !$acc loop gang private(av)
              DO x = 1, 30
                av = (a(x, y) + b(x, y) + c(x, y))/3
                !$acc loop vector
                DO z = 1, 30
                  d(x, y) = d(x, y) + (av + c(x, y))
                END DO  
              END DO
            !$acc end parallel
          END DO
       
        DO y = 1, 30
          DO x = 1, 30
            tmp(x, y) = ((a(x, y) + b(x, y) + c(x, y))/3) * 30
          END DO
        END DO
        DO y = 1, 30
          DO x = 1, 30
            IF (abs(tmp(x, y) - d(x, y)) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
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