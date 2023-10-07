!T1:variable predetermined data attributes,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER N
        PARAMETER (N=1024)
        INTEGER A(N), B(N), i

        A = 0
        B = 1
        
        DO i = 1, N
          A(i) = B(i)
        END DO
        
        ! OpenACC loop testing predetermined private variables attributes
        !$acc parallel loop
        DO i = 1, N
          A(i) = B(i) + 1
        END DO

        DO i = 1, N
          errors = errors + ABS(A(i) - B(i) - 1)
        END DO

        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
      END FUNCTION test1

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