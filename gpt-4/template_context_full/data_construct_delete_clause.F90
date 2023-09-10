#ifndef T1
!T1:data construct delete clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: arr(10)
        INTEGER :: i
        

        DO i = 1, 10
            arr(i) = i
        END DO

        !The $ACC DATA DELETE clause
        !$ACC DATA COPIN(arr)
        !$ACC PARALLEL LOOP
        DO i = 1, 10
           arr(i) = arr(i) + 1
        END DO
        !$ACC END PARALLEL LOOP
        !$ACC EXIT DATA DELETE(arr)

        DO i = 1, 10
            IF (arr(i) /= (i + 1)) THEN
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