!T1:parallel construct num_workers clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, PARAMETER :: N = 1000
        INTEGER :: i, sum
        INTEGER, DIMENSION(:), ALLOCATABLE :: array

        ALLOCATE(array(N))

        ! Initialize array
        DO i = 1, N
          array(i) = i
        END DO

        sum = 0

        !$acc parallel loop num_workers(4) copy(sum)
        DO i = 1, N
          sum = sum + array(i)
        END DO
        !$acc end parallel loop

        IF (sum .ne. 499500) THEN
          errors = errors + 1
        END IF

        DEALLOCATE(array)

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