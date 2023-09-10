#ifndef T1
!T1:loop construct private clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: A, B, C
        INTEGER :: N, i, j, k, tmp

        N = 100
        ALLOCATE(A(N), B(N), C(N))

        DO i = 1, N
           B(i) = i
           C(i) = 2 * i
           A(i) = 0
           !$acc loop private(tmp)
           DO j = 1, N
              tmp = B(j) + C(j)
              A(i) = A(i) + tmp
           END DO
        END DO

        ! Verification
        DO i = 1, N
           IF (A(i) /= (i + 2 * i) * N) THEN
             errors = errors + 1
           END IF
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