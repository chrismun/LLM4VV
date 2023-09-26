#ifndef T1
!T1:acc is present,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        REAL, DIMENSION(10) :: a
        LOGICAL :: is_present
        
        ! Initialize the array
        a = 1.0
        
        ! Test if the array is present in the current device memory
        is_present = acc_is_present(a)
        
        ! Check if the array is present
        IF (is_present) THEN
          errors = errors + 1
        END IF
        
        ! Check if there were any errors
        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif