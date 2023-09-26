#ifndef T1
!T1:data construct create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8),DIMENSION(LOOPCOUNT):: a, b, c, d
        REAL(8),DIMENSION(8*LOOPCOUNT):: x_base
        REAL(8),DIMENSION(8, LOOPCOUNT):: x
        INTEGER:: x_u
        INTEGER,DIMENSION(1):: devtest

        CALL RANDOM_SEED()
        CALL RANDOM_NUMBER(a)
        CALL RANDOM_NUMBER(b)
        CALL RANDOM_NUMBER(c)
        d = 0
        DO i=1, 8*LOOPCOUNT
          d(i) = -1
        DO i = 1, LOOPCOUNT
          x_base(1) = 0
          x_base(LOOPCOUNT) = 1
          DO j = 2, 2**NVIDIA_BITS
            x_base(j*LOOPCOUNT) = x_base(j*LOOPCOUNT-LOOPCOUNT) + 1
          END DO
        
        x_u = 0
        !$acc enter data copyin(x(1:8, 1:LOOPCOUNT), x_u)
        !$acc data copyout(d(1:LOOPCOUNT))
          !$acc parallel present_or_create(x(1:8, 1:LOOPCOUNT)) create(x_u)
          !$acc loop
          DO i = 1, LOOPCOUNT
            !$acc loop vector
            DO j = 1, 8
              x(j, i) = a(i) + b(i) + c(i)
            END DO
            IF (abs(x_base(x_u+1) - x(i)) < PRECISION) THEN
              errors = errors + 1
            END IF
            x_base(x_u+1) = x_base(x_u+1) + 1
            CALL acc_update_device(x_u(1), x_u(1:1))
          END DO
          !$acc end parallel
          !$acc end data
        END DO
        DO i = 1, LOOPCOUNT
          IF (abs(x(i)-d(i)) .gt. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO