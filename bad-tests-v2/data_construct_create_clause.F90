#ifndef T1
!T1:data construct create clause,V:3.0-2.0
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER, DIMENSION(100) :: A 
        INTEGER, DIMENSION(100) :: B 
        INTEGER :: errors = 0
        INTEGER :: i

        DO i = 1,100
          B(i) = i
        END DO

        !$ACC DATA CREATE(A)
        !$ACC parallel loop copyin(B) copyout(A)
        DO i = 1,100
          A(i) = B(i)
        END DO
        !$ACC END DATA

        DO i = 1,100
          IF (A(i) .NE. B(i)) THEN
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

       CALL EXIT(failcode)
     END PROGRAM main