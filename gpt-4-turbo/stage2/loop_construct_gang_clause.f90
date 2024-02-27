! This Fortran code tests the implementation of the OpenACC loop construct gang clause.
! It uses the parallel loop with the gang clause to fill an array and checks if the operation is performed correctly.

!T1:loop construct gang clause,V:2.7-2.3
      LOGICAL FUNCTION test_gang_clause()
        USE OPENACC
        IMPLICIT NONE

        INTEGER, PARAMETER :: N = 1024
        INTEGER :: i
        INTEGER, DIMENSION(N) :: result
        INTEGER :: errors = 0

        ! Initialize the result array
        result = 0

        ! Use the parallel construct with a loop and the gang clause.
        !$acc parallel
        !$acc loop gang
        DO i = 1, N
          result(i) = i
        END DO
        !$acc end parallel

        ! Check the results
        DO i = 1, N
          IF (result(i) /= i) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test_gang_clause = .FALSE.
        ELSE
          test_gang_clause = .TRUE.
        END IF
      END FUNCTION test_gang_clause

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        LOGICAL :: test_gang_clause
        failed = .FALSE.
        failcode = 0
        DO testrun = 1, 1  ! Only one test call since it's a simple verification test.
          failed = failed .or. test_gang_clause()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
        END IF
        CALL EXIT(failcode)
      END PROGRAM main