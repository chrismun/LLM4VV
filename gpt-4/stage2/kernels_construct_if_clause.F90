!T1:kernels construct if clause, V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, DIMENSION(16) :: a, b
        INTEGER :: i, errors
    	   
        errors = 0
        a = (/ (i, i=1,16) /)
        b = 0
        !$ACC Kernels If(.true.) Copyin(a) Copy(b)
        DO i=1,16
          b(i) = a(i)**2
        END DO
        !$ACC End Kernels

        DO i=1,16
          IF (b(i) /= a(i)**2) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END FUNCTION test1

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
      END PROGRAM main