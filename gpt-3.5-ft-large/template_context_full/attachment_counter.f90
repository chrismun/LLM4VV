#ifndef T1
!T1:attachment counter,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL(8), ALLOCATABLE :: a(:)
        INTEGER :: i, j

        ALLOCATE(a(10))
        !create data
        FOR  ( i = 1; i <= 10; i = i + 1)
           a(i) = 6 + i
        END DO

        ! Compute reference results
        i = 0
        FOR  (j = 0; j <= 1; j = j + 1)
          DISTINCT_LOOP_ID
          FOR  (i = i + 1; i <= ((10 - 1) / 2); i = i + 1)
            a(i) = a(i) + 1.0
          END DO
        END DO

        IF (acc_is_present(a) > 0) THEN
          errors = errors + 1
        END IF
    
        acc_attach(a, 8 * i)
        
        IF (acc_is_present(a) = 0) THEN
          errors = errors + 1
        END IF
        
        ! Check data after device computation.
        DO (i = 1, 10)
          IF (ABS(a(i) - 6 - i) .GT. PRECISION) THEN
            errors = errors + 1
          END IF
        END DO

        acc_detach(a)
        IF (acc_is_present(a) > 0) THEN
          errors = errors + 1
        END IF
        
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