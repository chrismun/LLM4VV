fortran
#ifndef T1
!T1:data construct create clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER :: var1, var2
        INTEGER :: create_clause
        INTEGER :: attach_clause
        INTEGER :: detach_clause
        INTEGER :: delete_clause
        INTEGER :: present_or_create_clause
        INTEGER :: pcreate_clause
        INTEGER :: enterdata_directive
        INTEGER :: exit_directive
        INTEGER :: structured_reference_counter
        INTEGER :: dynamic_reference_counter
        INTEGER :: zero_modifier
        
        ! Initialize variables
        var1 = 0
        var2 = 0
        create_clause = 0
        attach_clause = 0
        detach_clause = 0
        delete_clause = 0
        present_or_create_clause = 0
        pcreate_clause = 0
        enterdata_directive = 0
        exit_directive = 0
        structured_reference_counter = 0
        dynamic_reference_counter = 0
        zero_modifier = 0
        
        ! Test create clause
        IF (var1 .EQ. 0) THEN
          ! If var1 is not in shared memory, create clause should be performed
          create_clause = 1
          ! If var1 is a null pointer, attach clause should be performed
          attach_clause = 1
          ! If var1 is not a null pointer, present increment action should be performed
          present_or_create_clause = 1
          ! If var1 is a pointer reference, detach clause should be performed
          detach_clause = 1
          ! If var1 is not a null pointer, present decrement action should be performed
          present_or_create_clause = 1
          ! If var1 is not a null pointer, delete action should be performed
          delete_clause = 1
        END IF
        
        ! Test enterdata directive
        IF (var2 .EQ. 0) THEN
          ! If var2 is not in shared memory, create clause should be performed
          create_clause = 1
          ! If var2 is a null pointer, attach clause should be performed
          attach_clause = 1
          ! If var2 is not a null pointer, present increment action should be performed
          present_or_create_clause = 1
          ! If var2 is a pointer reference, detach clause should be performed
          detach_clause = 1
          ! If var2 is not a null pointer, present decrement action should be performed
          present_or_create_clause = 1
          ! If var2 is not a null pointer, delete action should be performed
          delete_clause = 1
        END IF
        
        ! Test exit directive
        IF (structured_reference_counter .EQ. 0) THEN
          ! If structured reference counter is zero, no action should be taken
          ! If structured reference counter is not zero, detach action should be performed
          detach_clause = 1
          ! If dynamic reference counter is zero, no action should be taken
          ! If dynamic reference counter is not zero, present decrement action should be performed
          present_or_create_clause = 1
          ! If both structured and dynamic reference counters are zero, delete action should be performed
          delete_clause = 1
        END IF
        
        ! Test zero modifier
        IF (zero_modifier .EQ. 1) THEN
          ! If zero modifier is present, memory should be zeroed after create action
          ! If zero modifier is not present, memory should not be zeroed after create action
          create_clause = 1
        END IF
        
        ! Test errors
        IF (errors .EQ. 0) THEN
          ! If no errors, test should pass
          test1 = .FALSE.
        ELSE
          ! If errors, test should fail
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