#ifndef T1
!T1:parallel construct reduction clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER, DIMENSION(1000):: array
        INTEGER :: num = 0
        INTEGER :: sum=0
        INTEGER :: i
        INTEGER :: errors = 0
 
        ! Initialize the array
        DO i=1, 1000
           array(i) = i
           sum = sum + i
        END DO

        ! Testing the reduction functionality
        !$acc parallel loop reduction(+:num)
        DO i=1, 1000
           num = num + array(i)
        END DO

        IF (num .ne. sum) THEN
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
      END PROGRAM main