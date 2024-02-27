!T1:parallel construct if clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: N = 1000
        REAL, DIMENSION(:), ALLOCATABLE :: a, b
        INTEGER :: i

        ALLOCATE(a(N), b(N))

        !$acc parallel if (N > 500) num_gangs(10) vector_length(32)
        !$acc loop gang worker vector
        DO i = 1, N
          a(i) = i * 1.0
          b(i) = i * 2.0
        END DO
        !$acc end parallel

        ! Verify the results
        DO i = 1, N
          IF (a(i) /= i * 1.0 .or. b(i) /= i * 2.0) THEN
            errors = errors + 1
          END IF
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