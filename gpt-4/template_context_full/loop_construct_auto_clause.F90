!.....begin modifications.....!
#ifndef T1
!T1:loop construct auto clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(:), ALLOCATABLE :: A, B
        INTEGER :: i, n
        
        n = 100
        ALLOCATE(A(n), B(n))
        
        !$ACC PARALLEL LOOP AUTO
        DO i = 1, n
            A(i) = B(i)
        END DO
        
        ! Verify if the loop has been implemented correctly
        DO i = 1, n
            IF (A(i) .ne. B(i)) THEN
                errors = errors + 1   
            END IF
        END DO
        
        DEALLOCATE(A, B)
        
        ! Checking if there were any errors
        IF (errors .eq. 0) THEN
          test1 = .TRUE.
        ELSE
          test1 = .FALSE.
        END IF
        END FUNCTION test1
#endif     

!.....end modifications.....!

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