fortran
#ifndef T1
!T1:data construct delete clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: var1, var2
        INTEGER :: ptr1, ptr2
        INTEGER :: dynamic_ref_counter1, dynamic_ref_counter2
        INTEGER :: structured_ref_counter1, structured_ref_counter2
        
        ! Initialize variables
        var1 = 1
        var2 = 2
        ptr1 = 1
        ptr2 = 2
        dynamic_ref_counter1 = 0
        dynamic_ref_counter2 = 0
        structured_ref_counter1 = 0
        structured_ref_counter2 = 0
        
        ! Test data construct delete clause
        !$acc data copy(var1, var2) delete(ptr1, ptr2)
        !$acc end data
        
        ! Check if delete clause worked correctly
        IF (dynamic_ref_counter1 .eq. 0 .and. dynamic_ref_counter2 .eq. 0) THEN
          ! Delete action should have been performed
          errors = errors + 1
        END IF
        
        ! Check if detach action was performed correctly
        IF (ptr1 .eq. 1 .and. ptr2 .eq. 2) THEN
          ! Detach action should have been performed
          errors = errors + 1
        END IF
        
        ! Check if present decrement action was performed correctly
        IF (structured_ref_counter1 .eq. 0 .and. structured_ref_counter2 .eq. 0) THEN
          ! Present decrement action should have been performed
          errors = errors + 1
        END IF
        
        ! Return errors
        test1 = errors .eq. 0
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