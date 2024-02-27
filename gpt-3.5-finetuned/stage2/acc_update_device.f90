!T1:acc update device,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), DIMENSION(LOOPCOUNT), TARGET :: A_host, A
        INTEGER :: x

        SEEDDIM(1) = 1
        SEEDDIM(1) = SEED
        CALL RANDOM_SEED(PUT=SEEDDIM)

        CALL RANDOM_NUMBER(A_host)

        !$acc data copyin(A_host(1:LOOPCOUNT)) create(A(1:LOOPCOUNT))
          CALL acc_update_device(A(1:LOOPCOUNT))
          !$acc parallel
            !$acc loop
            DO x = 1, LOOPCOUNT
              A(x) = A(x) + 1
            END DO
          !$acc end parallel
        !$acc end data

        DO x = 1, LOOPCOUNT
          IF (abs(A(x) - A_host(x) - 1) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1a = .FALSE.
        ELSE
          test1a = .TRUE.
        END IF

        END FUNCTION