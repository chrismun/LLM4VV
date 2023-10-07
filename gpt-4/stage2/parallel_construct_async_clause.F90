!T1:parallel construct async clause,V:2.7-2.3
      PROGRAM ACC_TEST
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        INTEGER :: errors = 0
        INTEGER, DIMENSION(1000) :: A, B, C
        INTEGER :: i
        
        !Initalize Arrays
        DO i=1, 1000
            A(i) = i
            B(i) = 2*i
            C(i) = 0
        END DO

        !Perform operation on device asynchronously
        !$ACC PARALLEL LOOP COPYIN(A,B) COPYOUT(C) ASYNC 
        DO i=1,1000
            C(i) = A(i) + B(i)
        END DO
        !$ACC WAIT 

        ! Verify results
        DO i=1,1000
            IF(C(i) .NE. A(i) + B(i)) THEN
                errors = errors + 1
            ENDIF
        END DO

        IF (errors .EQ. 0) THEN
           PRINT *, 'Test passed'
           CALL EXIT(0)
        ELSE
           PRINT *, 'Test failed with ', errors, 'errors'
           CALL EXIT(errors)
        END IF
      END PROGRAM ACC_TEST