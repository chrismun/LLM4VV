!T1:loop construct tile clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, PARAMETER :: N = 100
        INTEGER, PARAMETER :: TILE_SIZE = 10
        INTEGER :: i, j, sum1, sum2
        INTEGER :: errors = 0
        INTEGER, DIMENSION(N,N) :: a

        ! Initialize array
        DO j = 1, N
          DO i = 1, N
            a(i,j) = i + j
          END DO
        END DO

        ! Sum before tile clause
        sum1 = 0
        DO j = 1, N
          DO i = 1, N
            sum1 = sum1 + a(i,j)
          END DO
        END DO

        ! Apply tile clause
        !$acc data copy(a)
        !$acc parallel loop tile(TILE_SIZE,TILE_SIZE)
        DO j = 1, N
          DO i = 1, N
            a(i,j) = a(i,j) * 2
          END DO
        END DO
        !$acc end parallel loop
        !$acc end data

        ! Sum after tile clause
        sum2 = 0
        DO j = 1, N
          DO i = 1, N
            sum2 = sum2 + a(i,j)
          END DO
        END DO

        ! Check if sums are equal
        IF (sum1 .ne. sum2) THEN
          errors = errors + 1
        END IF

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