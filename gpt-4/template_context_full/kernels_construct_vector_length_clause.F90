#ifndef T1
!T1:kernels construct vector_length clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"

        INTEGER :: errors = 0
        INTEGER, DIMENSION(1024) :: A, B, C
        INTEGER :: i
        INTEGER, PARAMETER :: vector_length = 32

        A = (/ (i, i = 1, SIZE(A)) /)
        B = (/ (i, i = 1, SIZE(B)) /)

        !$ACC KERNELS VECTOR_LENGTH(vector_length)
        DO i = 1, SIZE(C)
          C(i) = A(i) + B(i)
        END DO
        !$ACC END KERNELS

        DO i = 1, SIZE(C)
          IF (C(i) /= A(i) + B(i)) THEN
            errors = errors + 1
          END IF
        END DO 

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode = 0, testrun
        LOGICAL :: failed = .FALSE.
        LOGICAL :: test1
        INCLUDE "acc_testsuite.Fh"

        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO

        IF (failed) THEN
          failcode = failcode + 1
        END IF

        CALL EXIT (failcode)
      END PROGRAM main