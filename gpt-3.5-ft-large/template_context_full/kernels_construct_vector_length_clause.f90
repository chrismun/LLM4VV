#ifndef T1
!T1:kernels construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
       
        INTEGER :: errors = 0
        REAL(8),DIMENSION(10000) :: a, b, c
        INTEGER k
        INTEGER,DIMENSION(1) :: a_device, b_device, c_device
        INTEGER :: length

        !dclare the device length, scaler length, init memory.	        
        length = 1
 
        !allocate and init arrays. 
        SEEDDIM(1) = 1 
        CALL RANDOM_SEED(PUT=SEEDDIM(1))

#       ifdef _OPENACC
        !$acc init
#       endif
        SEED = 436774653
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        c = 0

        !$acc enter data create(c(1:10000))
        !$acc enter data create(a(1:10000), b(1:10000))

        CALL acc_attach(GET_DEVICE_NUM(), a(1))
        CALL acc_attach(GET_DEVICE_NUM(), b(1))
        CALL acc_attach(GET_DEVICE_NUM(), c(1)) 
 
        DO k = 1, 100
          !$acc data copyout(c(1:10000))
            !$acc kernels vector_length(length)
            !$acc loop gang private(length)
            DO length = 1, 5 
              !$acc loop worker
              DO WHILE (length .lt. 5)
                 DO i = 1, 100
                  c(i) = c(i) + a(i) + b(i)
                END DO 
              END DO
            END DO
          !$acc end data
        END DO
        !$acc exit data copyout(a(1:10000), b(1:10000))

        DO i = 1, 10000
          IF (abs(c(i) - (a(i) + b(i))) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO 

        !$acc exit data delete(a(1:10000), b(1:10000), c(1:10000))

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