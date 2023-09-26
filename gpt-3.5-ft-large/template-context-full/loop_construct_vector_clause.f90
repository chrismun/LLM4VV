#ifndef T1
!T1:loop construct vector clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(10*P): a, b, c !Data length is 10

        SEEDDIM(1) = 1
         
        #pragma acc data copy(c(0:10*P)) copyin(a(0:10*P), b(0:10*P))
          #pragma acc kernels loop
          DO i = 1, 10 * P
            a(i) = GetRandomNumber(1)
            #pragma acc loop vector
            DO j = 1, i
              b(i) = GetRandomNumber(1)
              b(j) = GetRandomNumber(1)
              temp = (4 * a(i) + 2 * b(i))/i
              #pragma acc loop vector
              DO s = 1, i
                temp = temp - a(s)
              END DO
              c(i) = temp
            END DO
          END DO

        DO i = 0, 10*P
          data_test(a(i), b(i), c(i), i)
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