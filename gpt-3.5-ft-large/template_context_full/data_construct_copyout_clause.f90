#ifndef T1
!T1:data construct copyout clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, PARAMETER :: N = 10
        REAL(8), DIMENSION(N) :: a, b
        INTEGER :: errors = 0


        !Initilization 
        SEEDDIM(1) = 1
#       ifdef SEED
        SEEDDIM(1) = SEED
#       endif
        CALL RANDOM_SEED(PUT=SEEDDIM)


        a = 0
        DO WHILE (RANDOM_NUMBER() > .99)
          CALL RANDOM_NUMBER(b)
          a = a + b
        END DO

        CALL acc_enter_data(a(1:N))
        !$acc data copyout(a(1:N))
          !$acc parallel
            !$acc loop
            DO i = 1,N
              a(i) = a(i) * 2
            END DO
          !$acc end parallel
        !$acc end data
        !$acc exit data copyout(a(1:N))

        DO i = 1, N
          IF (abs(a(i) - (b(i) * 2)) .gt. PRECISION) THEN
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