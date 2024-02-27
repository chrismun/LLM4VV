!T1:parallel construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT, 50) :: a, b, c
        INTEGER :: x

        x = 42
        a = 0
        b = 0
        c = 0

        !$acc data copyin(a(1:LOOPCOUNT,1:50), b(1:LOOPCOUNT,1:50)) copyout(c(1:LOOPCOUNT,1:50))
          !$acc parallel vector_length(x)
            !$acc loop
            DO idx = 1, LOOPCOUNT
              DO j = 1, 50
                c(idx, j) = a(idx, j) + b(idx, j)
              END DO
            END DO
          !$acc end parallel
        !$acc end data

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
        LOGICAL :: test1
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
        CALL EXIT (failcode)
      END PROGRAM