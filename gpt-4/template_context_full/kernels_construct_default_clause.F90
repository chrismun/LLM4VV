!T1:kernels construct default clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
       
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER, DIMENSION(100) :: a, b, c
        INTEGER :: i

        DO i = 1, 100
          a(i) = i
          b(i) = 2*i
          c(i) = 0
        END DO

        !$ACC KERNELS DEFAULT(PRESENT)
        DO i = 1, 100
          c(i) = a(i) + b(i)
        END DO
        !$ACC END KERNELS 
        

        DO i = 1, 100
          IF (c(i) /= 3*i) THEN
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