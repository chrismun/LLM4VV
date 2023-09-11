fortran
#ifndef T1
!T1:data present clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: var1, var2
        INTEGER :: present_counter
        LOGICAL :: is_present
        
        ! Initialize variables
        var1 = 1
        var2 = 2
        present_counter = 0
        
        ! Attach var1 and var2 to the current device
        CALL acc_attach(var1)
        CALL acc_attach(var2)
        
        ! Increment the present counter for var1 and var2
        CALL acc_present_increment(var1)
        CALL acc_present_increment(var2)
        
        ! Check if var1 and var2 are present in the current device
        is_present = acc_present(var1) .AND. acc_present(var2)
        
        ! Decrement the present counter for var1 and var2
        CALL acc_present_decrement(var1)
        CALL acc_present_decrement(var2)
        
        ! Detach var1 and var2 from the current device
        CALL acc_detach(var1)
        CALL acc_detach(var2)
        
        ! Check if the present counter for var1 and var2 is zero
        IF (present_counter .EQ. 0) THEN
          ! If the present counter is zero, delete var1 and var2
          CALL acc_delete(var1)
          CALL acc_delete(var2)
        END IF
        
        ! Check if the present clause is working properly
        IF (is_present .EQV. .TRUE.) THEN
          errors = errors + 1
        END IF
        
        ! Return the number of errors
        test1 = errors .EQ. 0
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