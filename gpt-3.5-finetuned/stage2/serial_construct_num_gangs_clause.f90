!T1:serial construct num_gangs clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0

        REAL(8), ALLOCATABLE :: a(:,:), b(:,:)
        INTEGER :: x, y

        ALLOCATE(a(10, 10), b(10, 10))
        CALL RANDOM_NUMBER(a)
        b = 0

        !$acc data copyin(a(1:10, 1:10)) copyout(b(1:10, 1:10))
          !$acc serial num_gangs(5)
            !$acc loop gang
            DO x = 1, 10
              !$acc loop worker
              DO y = 1, 10
                b(x,y) = a(x,y)
              END DO
            END DO
          !$acc end serial
        !$acc end data

        DO x = 1, 10
          DO y = 1, 10
            IF (abs(a(x, y) - b(x, y)) .gt. PRECISION) THEN
              errors = errors + 1
            END IF
          END DO
        END DO
        DEALLOCATE(a, b)
      
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