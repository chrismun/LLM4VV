#ifndef T1
!T1:parallel construct wait clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0


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
     
#ifndef T1
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: x, y, z
        REAL(8),DIMENSION(LOOPCOUNT, 16):: a, b, c, d, e
        INTEGER,DIMENSION(1):: x_dev, y_dev
        INTEGER, POINTER :: cprivate


        !Initilization on the Host
        SEEDDIM(1) = 1
#       ifdef SEED
        SEEDDIM(1) = SEED
#       endif
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(d)
        
        !Compute on Device
        $ACC KERNEL PRESENT(x_dev, y_dev, c, a, b, d, e(1:LOOPCOUNT,1))
        $ACC LOOP
          DO x = 1, LOOPCOUNT
            e(x, 1) = 10
          END DO
          DO y = 2, 16
            DO x = 1, LOOPCOUNT
              e(x, y) = e(x, y - 1)
            END DO
          END DO
          DO z = 1, 16
            cprivate(1) = z
            DO x = 1, LOOPCOUNT
              e(x, z) = e(x, z) + a(x, z) + b(x, z) + d(x, z)
            END DO
          END DO
        $ACC END KERNEL
        DO x = 1, LOOPCOUNT
          IF (abs(e(x, 16) - (a(x, 16) + b(x, 16) + d(x, 16) + 16)) .gt. 1) THEN
            errors = errors + 1
          END IF
        END DO

        test1 = (errors .eq. 0)

      END
#endif