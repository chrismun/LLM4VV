#ifndef T1
!T1:loop construct collapse clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, PARAMETER :: N = 100
        REAL, DIMENSION(N,N) :: a, b, c
        INTEGER :: i, j, errors = 0

        ! Initialize arrays
        DO i = 1, N
          DO j = 1, N
            a(i,j) = i*j
            b(i,j) = i+j
          END DO
        END DO

        ! Perform operations on 2D array
        !$acc parallel loop collapse(2)
        DO i = 1, N
          DO j = 1, N
            c(i,j) = a(i,j) + b(i,j)
          END DO
        END DO

        ! Check results
        DO i = 1, N
          DO j = 1, N
            IF (c(i,j) .ne. a(i,j) + b(i,j)) THEN
              errors = errors + 1
            END IF
          END DO
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