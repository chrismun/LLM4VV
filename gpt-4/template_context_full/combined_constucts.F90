!T1:combined constucts,V:2.7-2.3
#include "acc_testsuite.Fh"

      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INTEGER, DIMENSION(1000) :: a
        INTEGER, DIMENSION(1000) :: b
        INTEGER, DIMENSION(1000) :: c
        INTEGER :: i
        INTEGER :: num_errors
        
        num_errors = 0
        DO i=1,1000
            a(i) = i
            b(i) = 1000 - i
            c(i) = 0
        END DO
        
        !$acc parallel loop
        DO i=1,1000
            c(i) = a(i) + b(i)
        END DO
        
        DO i=1,1000
            IF (c(i) .ne. 1000) THEN
                num_errors = num_errors + 1
            END IF
        END DO

        IF (num_errors .eq. 0) THEN
            test1 = .TRUE.
        ELSE
            test1 = .FALSE.
        END IF
      END FUNCTION test1

      PROGRAM main
        IMPLICIT NONE
        LOGICAL :: test1
        INTEGER :: failcode
        failcode = 0
          
        IF (.not. test1()) THEN
            failcode = 1
        END IF
        
        STOP failcode
      END PROGRAM main