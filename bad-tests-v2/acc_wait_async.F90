#ifndef T1
!T1:acc wait async,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: A, B, C
        INTEGER :: i

        A = (/ (i, i=1, 10) /)
        B = (/ (i, i=1, 10) /)
        C = 0

        !$ACC Kernels
        DO i = 1, 10
           C(i) = A(i) + B(i)
        END DO
        !$ACC End Kernels 
            
        !$ACC Wait

        CALL acc_wait_async(1,1)

        DO i = 1, 10
           IF (C(i) /= A(i) + B(i)) THEN
              errors = errors + 1;
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
        LOGICAL, EXTERNAL :: test1
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