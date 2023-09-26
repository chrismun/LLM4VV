#ifndef T1
!T1:loop construct tile clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, PARAMETER :: N=1024, M=512
        INTEGER :: i, j, errors = 0
        REAL, DIMENSION(N,M) :: A, B

! Initialize data
        DO j = 1, M
            DO i = 1, N
                A(i,j) = 1.0 * i + j
                B(i,j) = 0.0
            END DO
        END DO

! Perform computation with tile clause
        !$acc parallel loop collapse(2) tile(128,64) copyout(B) copyin(A)
        DO j = 1, M
            DO i = 1, N
                B(i,j) = A(i,j) * 2.0
            END DO
        END DO

! Check results
        DO j = 1, M
            DO i = 1, N
                IF (B(i,j) /= A(i,j) * 2.0) THEN
                    errors = errors + 1
                END IF
            END DO
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1
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
      END PROGRAM main