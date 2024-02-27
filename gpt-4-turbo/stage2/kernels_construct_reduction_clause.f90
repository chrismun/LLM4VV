!T1:kernels construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, PARAMETER :: N = 1024
        REAL :: a(N)
        REAL :: total, expected
        INTEGER :: i,errors

        errors = 0
        total = 0.0
        expected = 0.0

        ! Initialize a
        DO i = 1, N
           a(i) = 1.0
           expected = expected + a(i)
        END DO

        ! Apply OpenACC kernels reduction
        !$acc kernels reduction(+:total)
        DO i = 1, N
           total = total + a(i)
        END DO
        !$acc end kernels

        ! Check if the reduction result is correct
        IF (ABS(total - expected) > 1.0E-5) THEN
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
        EXTERNAL test1
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