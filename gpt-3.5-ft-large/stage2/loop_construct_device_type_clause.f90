#ifndef T1
!T1:loop construct device_type clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        !The OpenACC loop construct is executed on the device with the device_type clause with execuiton on the device that the data acc_d resides on and compare the results on the host
        REAL(8),DIMENSION(10,10,10):: a
        REAL(8),DIMENSION(10,10,10):: b
        REAL(8),DIMENSION(10,10,10),DEVICE:: c
        INTEGER,DIMENSION(1):: errors_in
        INTEGER:: x, y, z

        !initilization
        SEEDDIM(1) = 1
#       ifdef SEED
        SEEDDIM(1) = SEED
#       endif
        CALL RANDOM_SEED(PUT=SEEDDIM)
        CALL RANDOM_NUMBER(a)
        b = 0

        !$acc data copyin(a(1:10,1:10,1:10)) create(c(1:10,1:10,1:10))
          !$acc kernels
            !$acc loop device_type(plain), independent
            DO y = 1, 10
              DO x = 1, 10
                DO z = 1, 10
                  c(y,x,z) = a(y,x,z)
                END DO
              END DO
            END DO
            !$acc loop device_type(vector)
            DO y = 1, 10
              DO x = 1, 10
                DO z = 1, 10
                  c(y,x,z) = c(y,x,z) + a(y,x,z)
                END DO
              END DO
            END DO
          !$acc end kernels
        !$acc end data

        DO x = 1, 10
          DO y = 1, 10
            DO z = 1, 10
              b(x, y, z) = b(x, y, z) + a(x, y, z)
            END DO
          END DO
        END DO
           IF (IS_ACC_PRESENT(errors_in(1)))) THEN
            DO x = 1, 10
              DO y = 1, 10
                DO z = 1, 10
                  IF (abs(c(x, y, z) - b(x, y, z)) .gt. PRECISION) THEN
                    errors = errors + 1
                  END IF
                END DO
              END DO
            END DO
          END IF

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